/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2014-2017 Inviwo Foundation
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

#include <modules/opengl/shader/shader.h>
#include "volumegradientprocessor.h"

namespace inviwo {
const ProcessorInfo VolumeGradientProcessor::processorInfo_{
    "org.inviwo.VolumeGradient",  // Class identifier
    "Volume Gradient",            // Display name
    "Volume Operation",           // Category
    CodeState::Stable,            // Code state
    Tags::GL,                     // Tags
};
const ProcessorInfo VolumeGradientProcessor::getProcessorInfo() const {
    return processorInfo_;
}

VolumeGradientProcessor::VolumeGradientProcessor()
    : VolumeGLProcessor("volume_gradient.frag")
    , channel_("channel", "Channel")
    , dataInChannel4_("dataInChannel4_", "Store Input Data in Alpha", false,
                      InvalidationLevel::InvalidResources) {
    this->dataFormat_ = DataVec3Float32::get();

    channel_.addOption("Channel 1", "Channel 1", 0);
    channel_.setCurrentStateAsDefault();

    inport_.onChange(this, &VolumeGradientProcessor::onVolumeChange);

    addProperty(channel_);
    addProperty(dataInChannel4_);
}

VolumeGradientProcessor::~VolumeGradientProcessor() {}

void VolumeGradientProcessor::preProcess(TextureUnitContainer &) {
    shader_.setUniform("channel", channel_.getSelectedValue());
}

void VolumeGradientProcessor::postProcess() {
    volume_->dataMap_.dataRange = dvec2(-1.0, 1.0);
}

void VolumeGradientProcessor::initializeResources() {
    if (dataInChannel4_.get()) {
        shader_.getFragmentShaderObject()->addShaderDefine("ADD_DATA_CHANNEL");
        this->dataFormat_ = DataVec4Float32::get();
    } else {
        shader_.getFragmentShaderObject()->removeShaderDefine("ADD_DATA_CHANNEL");
        this->dataFormat_ = DataVec3Float32::get();
    }
    shader_.build();
    internalInvalid_ = true;
}

void VolumeGradientProcessor::onVolumeChange() {
    if (inport_.hasData()) {
        int channels = static_cast<int>(inport_.getData()->getDataFormat()->getComponents());

        if (channels == static_cast<int>(channel_.size())) return;

        channel_.clearOptions();
        for (int i = 0; i < channels; i++) {
            std::stringstream ss;
            ss << "Channel " << i;
            channel_.addOption(ss.str(), ss.str(), i);
        }
        channel_.setCurrentStateAsDefault();
    }
}

}  // namespace

