/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2012-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include "volumeraycaster.h"
#include <inviwo/core/ports/imageport.h>
#include <inviwo/core/io/serialization/serialization.h>
#include <inviwo/core/io/serialization/versionconverter.h>
#include <inviwo/core/interaction/events/keyboardevent.h>
#include <modules/opengl/volume/volumegl.h>
#include <modules/opengl/shader/shader.h>
#include <modules/opengl/texture/textureunit.h>
#include <modules/opengl/texture/textureutils.h>
#include <modules/opengl/shader/shaderutils.h>
#include <modules/opengl/volume/volumeutils.h>
#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/util/rendercontext.h>

namespace inviwo {

const ProcessorInfo VolumeRaycaster::processorInfo_{
    "org.inviwo.VolumeRaycaster",  // Class identifier
    "Volume Raycaster",            // Display name
    "Volume Rendering",            // Category
    CodeState::Stable,             // Code state
    Tags::GL                       // Tags
};

VolumeRaycaster::VolumeRaycaster()
    : Processor()
    , shader_("raycasting.frag", false)
    , volumePort_("volume")
    , entryPort_("entry")
    , exitPort_("exit")
    , backgroundPort_("bg")
    , outport_("outport")
    , transferFunction_("transferFunction", "Transfer function", &volumePort_)
    , channel_("channel", "Render Channel")
    , raycasting_("raycaster", "Raycasting")
    , camera_("camera", "Camera")
    , lighting_("lighting", "Lighting", &camera_)
    , positionIndicator_("positionindicator", "Position Indicator")
    , toggleShading_("toggleShading", "Toggle Shading", [this](Event* e) { toggleShading(e); },
                     IvwKey::L) {
                     
    shader_.onReload([this]() { invalidate(InvalidationLevel::InvalidResources); });

    addPort(volumePort_, "VolumePortGroup");
    addPort(entryPort_, "ImagePortGroup1");
    addPort(exitPort_, "ImagePortGroup1");
    addPort(outport_, "ImagePortGroup1");
    addPort(backgroundPort_ ,"ImagePortGroup1");

    backgroundPort_.setOptional(true);

    channel_.addOption("Channel 1", "Channel 1", 0);
    channel_.setSerializationMode(PropertySerializationMode::All);
    channel_.setCurrentStateAsDefault();

    volumePort_.onChange(this, &VolumeRaycaster::onVolumeChange);
    backgroundPort_.onConnect([&]() { this->invalidate(InvalidationLevel::InvalidResources); });
    backgroundPort_.onDisconnect([&]() { this->invalidate(InvalidationLevel::InvalidResources); });

    // change the currently selected channel when a pre-computed gradient is selected
    raycasting_.gradientComputationMode_.onChange([this]() {
        if (channel_.size() == 4) {
            if (raycasting_.gradientComputationMode_.isSelectedIdentifier("precomputedXYZ")) {
                channel_.set(3);
            } else if (raycasting_.gradientComputationMode_.isSelectedIdentifier(
                           "precomputedYZW")) {
                channel_.set(0);
            }
        }
    });

    addProperty(channel_);
    addProperty(transferFunction_);
    addProperty(raycasting_);
    addProperty(camera_);
    addProperty(lighting_);
    addProperty(positionIndicator_);
    addProperty(toggleShading_);
}

const ProcessorInfo VolumeRaycaster::getProcessorInfo() const {
    return processorInfo_;
}

void VolumeRaycaster::initializeResources() {
    utilgl::addShaderDefines(shader_, raycasting_);
    utilgl::addShaderDefines(shader_, camera_);
    utilgl::addShaderDefines(shader_, lighting_);
    utilgl::addShaderDefines(shader_, positionIndicator_);
    utilgl::addShaderDefinesBGPort(shader_, backgroundPort_);
    shader_.build();
}

void VolumeRaycaster::onVolumeChange() {
    if (volumePort_.hasData()) {
        size_t channels = volumePort_.getData()->getDataFormat()->getComponents();

        if (channels == channel_.size()) return;

        std::vector<OptionPropertyIntOption> channelOptions;
        for (size_t i = 0; i < channels; i++) {
            channelOptions.emplace_back("Channel " + toString(i+1), "Channel " + toString(i+1),
                                        static_cast<int>(i));
        }
        channel_.replaceOptions(channelOptions);
        channel_.setCurrentStateAsDefault();
    }
}

void VolumeRaycaster::process() {
    if (volumePort_.isChanged()) {
        auto newVolume = volumePort_.getData();

        if (newVolume->hasRepresentation<VolumeGL>()) {
            loadedVolume_ = newVolume;
        } else {
            dispatchPool([this, newVolume]() {
                RenderContext::getPtr()->activateLocalRenderContext();
                newVolume->getRep<kind::GL>();
                glFinish();
                dispatchFront([this, newVolume]() {
                    loadedVolume_ = newVolume;
                    invalidate(InvalidationLevel::InvalidOutput);
                });
            });
        }
    }

    if (!loadedVolume_) return;
    if (!loadedVolume_->hasRepresentation<VolumeGL>()) {
        LogWarn("No GL rep !!!");
        return;
    }

    utilgl::activateAndClearTarget(outport_);
    shader_.activate();

    TextureUnitContainer units;
    utilgl::bindAndSetUniforms(shader_, units, *loadedVolume_, "volume");
    utilgl::bindAndSetUniforms(shader_, units, transferFunction_);
    utilgl::bindAndSetUniforms(shader_, units, entryPort_, ImageType::ColorDepthPicking);
    utilgl::bindAndSetUniforms(shader_, units, exitPort_, ImageType::ColorDepth);
    if(backgroundPort_.isConnected()){
        utilgl::bindAndSetUniforms(shader_, units, backgroundPort_, ImageType::ColorDepthPicking);
    }
    utilgl::setUniforms(shader_, outport_, camera_, lighting_, raycasting_, positionIndicator_,
                        channel_);

    utilgl::singleDrawImagePlaneRect();

    shader_.deactivate();
    utilgl::deactivateCurrentTarget();
}

void VolumeRaycaster::toggleShading(Event*) {
    if (lighting_.shadingMode_.get() == ShadingMode::None) {
        lighting_.shadingMode_.set(ShadingMode::Phong);
    } else {
        lighting_.shadingMode_.set(ShadingMode::None);
    }
}

// override to do member renaming.
void VolumeRaycaster::deserialize(Deserializer& d) {
    util::renamePort(d, {{&entryPort_, "entry-points"}, {&exitPort_, "exit-points"}});
    Processor::deserialize(d);
}

}  // namespace
