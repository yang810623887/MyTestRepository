/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2017 Inviwo Foundation
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

#include "streamribbons.h"
#include <inviwo/core/datastructures/geometry/basicmesh.h>
#include <inviwo/core/datastructures/volume/volume.h>
#include <inviwo/core/datastructures/volume/volumeram.h>
#include <inviwo/core/datastructures/buffer/bufferramprecision.h>
#include <inviwo/core/util/imagesampler.h>

namespace inviwo {

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo StreamRibbons::processorInfo_{
    "org.inviwo.StreamRibbons",    // Class identifier
    "Stream Ribbons",              // Display name
    "Vector Field Visualization",  // Category
    CodeState::Experimental,       // Code state
    Tags::CPU,                     // Tags
};
const ProcessorInfo StreamRibbons::getProcessorInfo() const {
    return processorInfo_;
}

StreamRibbons::StreamRibbons()
    : Processor()
    , sampler_("sampler")
    , vorticitySampler_("vorticitySampler")
    , seedPoints_("seedpoints")
    , colors_("colors")
    , volume_("vectorVolume")
    , vorticityVolume_("vorticityVolume")
    , streamLineProperties_("streamLineProperties", "Stream Line Properties")
    , ribbonWidth_("ribbonWidth", "Ribbon Width", 0.1f, 0.00001f)
    , tf_("transferFunction", "Transfer Function")
    , coloringMethod_("coloringMethod", "Color by")
    , velocityScale_("velocityScale_", "Velocity Scale (inverse)", 1, 0, 10)
    , maxVelocity_("minMaxVelocity", "Max Velocity", "0", InvalidationLevel::Valid)
    , maxVorticity_("maxVorticity", "Max Vorticity", "0", InvalidationLevel::Valid)
    , mesh_("mesh")
{
    addPort(sampler_);
    addPort(vorticitySampler_);
    addPort(seedPoints_);
    addPort(colors_);
    addPort(volume_);
    addPort(vorticityVolume_);
    addPort(mesh_);

    colors_.setOptional(true);
    
    addProperty(streamLineProperties_);
    addProperty(ribbonWidth_);

    addProperty(tf_);
    addProperty(coloringMethod_);
    addProperty(velocityScale_);
    addProperty(maxVelocity_);
    addProperty(maxVorticity_);

    maxVelocity_.setReadOnly(true);
    maxVorticity_.setReadOnly(true);

    coloringMethod_.addOption("vel", "Velocity", ColoringMethod::Velocity);
    coloringMethod_.addOption("vorticity", "Vorticity", ColoringMethod::Vorticity);
    coloringMethod_.addOption("port", "Colors in port", ColoringMethod::ColorPort);

    setAllPropertiesCurrentStateAsDefault();
}

void StreamRibbons::process() {
    //*
    auto sampler = [&]() -> std::shared_ptr<const SpatialSampler<3, 3, double> > {
        if (sampler_.isConnected()) return sampler_.getData();
        else return std::make_shared<VolumeDoubleSampler<3>>(volume_.getData());
    }();


    auto vorticitySampler = [&]() -> std::shared_ptr<const SpatialSampler<3, 3, double> > {
        if (vorticitySampler_.isConnected()) return vorticitySampler_.getData();
        else return std::make_shared<VolumeDoubleSampler<3>>(vorticityVolume_.getData());
    }();


    auto mesh = std::make_shared<BasicMesh>();
    mesh->setModelMatrix(sampler->getModelMatrix());
    mesh->setWorldMatrix(sampler->getWorldMatrix());

    auto m = streamLineProperties_.getSeedPointTransformationMatrix(
        sampler->getCoordinateTransformer());
    double maxVelocity = 0;
    double maxVorticity = 0;
    StreamLineTracer tracer(sampler, streamLineProperties_);
    ImageSampler tf(tf_.get().getData());
    tracer.addMetaSampler("vorticity", vorticitySampler);
  //  mat3 invBasis = glm::inverse(vectorVolume_.getData()->getBasis());
    mat3 invBasis;
    std::vector<BasicMesh::Vertex> vertices;


    bool hasColors = colors_.hasData();
    size_t lineId = 0;

    for (const auto &seeds : seedPoints_) {
        for (auto &p : (*seeds)) {
            vec4 P = m * vec4(p, 1.0f);
            auto line = tracer.traceFrom(vec3(P));

            auto position = line.getPositions().begin();
            auto velocity = line.getMetaData("velocity").begin();
            auto vorticity = line.getMetaData("vorticity").begin();

            auto size = line.getPositions().size();
            if (size <= 1) continue;
            auto indexBuffer = mesh->addIndexBuffer(DrawType::Triangles, ConnectivityType::Strip);
            indexBuffer->getDataContainer().reserve(size);


            vec4 c;
            if (hasColors) {
                if (lineId >= colors_.getData()->size()) {
                    LogWarn("The vector of colors is smaller then the vector of seed points");
                }
                else {
                    c = colors_.getData()->at(lineId);
                }
            }
            lineId++;


            for (size_t i = 0; i < size; i++) {
                auto vort = invBasis * glm::normalize(vec3(*vorticity));
                auto velo = invBasis * glm::normalize(vec3(*velocity));
                auto N = glm::normalize(glm::cross(vort, velo));
                vort *= (0.5f * ribbonWidth_.get());
                auto velocityMagnitude = glm::length(*velocity);
                auto vortictyMagnitude = glm::length(*vorticity);

                maxVelocity = std::max(maxVelocity, velocityMagnitude);
                maxVorticity = std::max(maxVorticity, vortictyMagnitude);

                vec3 p0 = vec3(*position) - vort;
                vec3 p1 = vec3(*position) + vort;

                
                float d;
                switch (coloringMethod_.get())
                {
                case ColoringMethod::Vorticity:
                    d = glm::clamp(static_cast<float>(vortictyMagnitude) / velocityScale_.get(), 0.0f, 1.0f);
                    c = vec4(tf.sample(dvec2(d, 0.0)));
                    break;
                case ColoringMethod::ColorPort:
                    if (hasColors) { 
                        break;
                    }
                    else {
                        LogWarn("No colors in the color port, using velocity for coloring instead ");
                    }
                case ColoringMethod::Velocity:
                    d = glm::clamp(static_cast<float>(velocityMagnitude) / velocityScale_.get(), 0.0f, 1.0f);
                    c = vec4(tf.sample(dvec2(d, 0.0)));
                default:
                    break;
                }
               

                indexBuffer->add(static_cast<std::uint32_t>(vertices.size()));
                indexBuffer->add(static_cast<std::uint32_t>(vertices.size()+1));
                vertices.push_back({ p0, N, p0, c });
                vertices.push_back({ p1, N, p1, c });

                position++;
                velocity++;
                vorticity++;
            }
        }

        maxVelocity_.set(toString(maxVelocity));
        maxVorticity_.set(toString(maxVorticity));
    }
    mesh->addVertices(vertices);
    mesh_.setData(mesh);
 //   */
}

}  // namespace

