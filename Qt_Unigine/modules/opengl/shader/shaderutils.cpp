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

#include <inviwo/core/datastructures/coordinatetransformer.h>
#include <modules/opengl/shader/shaderutils.h>
#include <modules/opengl/shader/shadermanager.h>

namespace inviwo {

namespace utilgl {

void addShaderDefines(Shader& shader, const SimpleLightingProperty& property) {
    addShaderDefines(shader, ShadingMode::Modes(property.shadingMode_.get()));
}

void addShaderDefines(Shader& shader, const ShadingMode::Modes& mode) {
    // implementations in  modules/opengl/glsl/utils/shading.glsl
    std::string shadingKey =
        "APPLY_LIGHTING(lighting, materialAmbientColor, materialDiffuseColor, "
        "materialSpecularColor, position, normal, toCameraDir)";
    std::string shadingValue = "";

    switch (mode) {
        case ShadingMode::Ambient:
            shadingValue = "shadeAmbient(lighting, materialAmbientColor);";
            break;
        case ShadingMode::Diffuse:
            shadingValue = "shadeDiffuse(lighting, materialDiffuseColor, position, normal);";
            break;
        case ShadingMode::Specular:
            shadingValue =
                "shadeSpecular(lighting, materialSpecularColor, position, normal, toCameraDir);";
            break;
        case ShadingMode::BlinnPhong:
            shadingValue =
                "shadeBlinnPhong(lighting, materialAmbientColor, materialDiffuseColor, "
                "materialSpecularColor, position, normal, toCameraDir);";
            break;
        case ShadingMode::Phong:
            shadingValue =
                "shadePhong(lighting, materialAmbientColor, materialDiffuseColor, "
                "materialSpecularColor, position, normal, toCameraDir);";
            break;
        case ShadingMode::None:
        default:
            shadingValue = "materialAmbientColor;";
            break;
    }

    shader.getFragmentShaderObject()->addShaderDefine(shadingKey, shadingValue);
}

void setShaderUniforms(Shader& shader, const SimpleLightingProperty& property, std::string name) {
    shader.setUniform(name + ".position", property.getTransformedPosition());
    shader.setUniform(name + ".ambientColor", property.ambientColor_.get());
    shader.setUniform(name + ".diffuseColor", property.diffuseColor_.get());
    shader.setUniform(name + ".specularColor", property.specularColor_.get());
    shader.setUniform(name + ".specularExponent", property.specularExponent_.get());
}

void addShaderDefines(Shader& /*shader*/, const CameraProperty& /*property*/) {}

void setShaderUniforms(Shader& shader, const CameraProperty& property, std::string name) {
    shader.setUniform(name + ".worldToView", property.viewMatrix());
    shader.setUniform(name + ".viewToWorld", property.inverseViewMatrix());
    shader.setUniform(name + ".worldToClip", property.projectionMatrix() * property.viewMatrix());
    shader.setUniform(name + ".viewToClip", property.projectionMatrix());
    shader.setUniform(name + ".clipToView", property.inverseProjectionMatrix());
    shader.setUniform(name + ".clipToWorld",
                      property.inverseViewMatrix() * property.inverseProjectionMatrix());
    shader.setUniform(name + ".position", property.getLookFrom());
    shader.setUniform(name + ".nearPlane", property.getNearPlaneDist());
    shader.setUniform(name + ".farPlane", property.getFarPlaneDist());
}

void setShaderUniforms(Shader& shader, const Camera& property, std::string name) {
    shader.setUniform(name + ".worldToView", property.getViewMatrix());
    shader.setUniform(name + ".viewToWorld", property.getInverseViewMatrix());
    shader.setUniform(name + ".worldToClip",
                      property.getProjectionMatrix() * property.getViewMatrix());
    shader.setUniform(name + ".viewToClip", property.getProjectionMatrix());
    shader.setUniform(name + ".clipToView", property.getInverseProjectionMatrix());
    shader.setUniform(name + ".clipToWorld",
                      property.getInverseViewMatrix() * property.getInverseProjectionMatrix());
    shader.setUniform(name + ".position", property.getLookFrom());
    shader.setUniform(name + ".nearPlane", property.getNearPlaneDist());
    shader.setUniform(name + ".farPlane", property.getFarPlaneDist());
}

void setShaderUniforms(Shader& shader, const SpatialEntity<3>& object, const std::string& name) {
    const SpatialCoordinateTransformer<3>& ct = object.getCoordinateTransformer();

    mat4 dataToWorldMatrix = ct.getDataToWorldMatrix();
    mat4 modelToWorldMatrix = ct.getModelToWorldMatrix();

    shader.setUniform(name + ".dataToModel", ct.getDataToModelMatrix());
    shader.setUniform(name + ".modelToData", ct.getModelToDataMatrix());

    shader.setUniform(name + ".dataToWorld", dataToWorldMatrix);
    shader.setUniform(name + ".worldToData", ct.getWorldToDataMatrix());

    shader.setUniform(name + ".modelToWorld", modelToWorldMatrix);
    shader.setUniform(name + ".worldToModel", ct.getWorldToModelMatrix());
    shader.setUniform(name + ".modelToWorldNormalMatrix",
                      glm::mat3(glm::transpose(glm::inverse(modelToWorldMatrix))));

    shader.setUniform(name + ".dataToWorldNormalMatrix",
                      glm::mat3(glm::transpose(glm::inverse(dataToWorldMatrix))));
}

void addShaderDefines(Shader& shader, const SimpleRaycastingProperty& property) {
    // gradient for channel 1
    std::string gradientComputationKey = "COMPUTE_GRADIENT(voxel, volume, volumeParams, samplePos)";
    // gradient for specific channel
    std::string singleChannelGradientKey =
        "COMPUTE_GRADIENT_FOR_CHANNEL(voxel, volume, volumeParams, samplePos, channel)";
    // gradients for all channels
    std::string allChannelsGradientKey =
        "COMPUTE_ALL_GRADIENTS(voxel, volume, volumeParams, samplePos)";

    std::string gradientValue = "";
    std::string singleChannelGradientValue = "";
    std::string allChannelsGradientValue = "";
    std::string channel = "channel";
    std::string defaultChannel = "0";

    if (property.classificationMode_.isSelectedIdentifier("voxel-value")) {
        channel = "3";
        defaultChannel = "3";
    }

    if (property.gradientComputationMode_.isSelectedIdentifier("none")) {
        gradientValue = "vec3(0)";
        singleChannelGradientValue = "vec3(0)";
        allChannelsGradientValue = "mat4x3(0)";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("forward")) {
        gradientValue =
            "gradientForwardDiff(voxel, volume, volumeParams, samplePos, " + defaultChannel + ");";
        singleChannelGradientValue =
            "gradientForwardDiff(voxel, volume, volumeParams, samplePos, " + channel + ");";
        allChannelsGradientValue =
            "gradientAllForwardDiff(voxel, volume, volumeParams, samplePos);";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("central")) {
        gradientValue =
            "gradientCentralDiff(voxel, volume, volumeParams, samplePos, " + defaultChannel + ");";
        singleChannelGradientValue =
            "gradientCentralDiff(voxel, volume, volumeParams, samplePos, " + channel + ");";
        allChannelsGradientValue =
            "gradientAllCentralDiff(voxel, volume, volumeParams, samplePos);";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("central-higher")) {
        gradientValue =
            "gradientCentralDiffH(voxel, volume, volumeParams, samplePos, " + defaultChannel + ");";
        singleChannelGradientValue =
            "gradientCentralDiffH(voxel, volume, volumeParams, samplePos, " + channel + ");";
        allChannelsGradientValue =
            "gradientAllCentralDiffH(voxel, volume, volumeParams, samplePos);";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("backward")) {
        gradientValue =
            "gradientBackwardDiff(voxel, volume, volumeParams, samplePos, " + defaultChannel + ");";
        singleChannelGradientValue =
            "gradientBackwardDiff(voxel, volume, volumeParams, samplePos, " + channel + ");";
        allChannelsGradientValue =
            "gradientAllBackwardDiff(voxel, volume, volumeParams, samplePos);";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("precomputedXYZ")) {
        gradientValue = "gradientPrecomputedXYZ(voxel, volumeParams);";
        singleChannelGradientValue = "gradientPrecomputedXYZ(voxel, volumeParams);";
        allChannelsGradientValue = "gradientPrecomputedXYZ(voxel, volumeParams);";
    } else if (property.gradientComputationMode_.isSelectedIdentifier("precomputedYZW")) {
        gradientValue = "gradientPrecomputedYZW(voxel, volumeParams);";
        singleChannelGradientValue = "gradientPrecomputedYZW(voxel, volumeParams);";
        allChannelsGradientValue = "gradientPrecomputedYZW(voxel, volumeParams);";
    }

    shader.getFragmentShaderObject()->addShaderDefine(gradientComputationKey, gradientValue);
    shader.getFragmentShaderObject()->addShaderDefine(singleChannelGradientKey,
                                                      singleChannelGradientValue);
    shader.getFragmentShaderObject()->addShaderDefine(allChannelsGradientKey,
                                                      allChannelsGradientValue);

    // classification defines, red channel is used
    std::string classificationKey = "APPLY_CLASSIFICATION(transferFunc, voxel)";
    std::string classificationValue = "";
    if (property.classificationMode_.isSelectedIdentifier("none"))
        classificationValue = "vec4(voxel.r);";
    else if (property.classificationMode_.isSelectedIdentifier("transfer-function"))
        classificationValue = "applyTF(transferFunc, voxel.r);";
    else if (property.classificationMode_.isSelectedIdentifier("voxel-value"))
        classificationValue = "voxel;";
    shader.getFragmentShaderObject()->addShaderDefine(classificationKey, classificationValue);

    // classification of specific channel
    classificationKey = "APPLY_CHANNEL_CLASSIFICATION(transferFunc, voxel, channel)";
    classificationValue = "";
    if (property.classificationMode_.isSelectedIdentifier("none"))
        classificationValue = "vec4(voxel[channel]);";
    else if (property.classificationMode_.isSelectedIdentifier("transfer-function"))
        classificationValue = "applyTF(transferFunc, voxel, channel);";
    else if (property.classificationMode_.isSelectedIdentifier("voxel-value"))
        classificationValue = "voxel;";
    shader.getFragmentShaderObject()->addShaderDefine(classificationKey, classificationValue);

    // compositing defines
    std::string compositingKey =
        "APPLY_COMPOSITING(result, color, samplePos, voxel, gradient, camera, isoValue, t, tDepth, "
        "tIncr)";
    std::string compositingValue;

    if (property.compositingMode_.isSelectedIdentifier("dvr"))
        compositingValue = "compositeDVR(result, color, t, tDepth, tIncr);";
    else if (property.compositingMode_.isSelectedIdentifier("mip"))
        compositingValue = "compositeMIP(result, color, t, tDepth);";
    else if (property.compositingMode_.isSelectedIdentifier("fhp"))
        compositingValue = "compositeFHP(result, color, samplePos, t, tDepth);";
    else if (property.compositingMode_.isSelectedIdentifier("fhn"))
        compositingValue = "compositeFHN(result, color, gradient, t, tDepth);";
    else if (property.compositingMode_.isSelectedIdentifier("fhnvs"))
        compositingValue = "compositeFHN_VS(result, color, gradient, t, camera, tDepth);";
    else if (property.compositingMode_.isSelectedIdentifier("fhd"))
        compositingValue = "compositeFHD(result, color, t, tDepth);";
    else if (property.compositingMode_.isSelectedIdentifier("iso"))
        compositingValue = "compositeISO(result, color, voxel.r, t, tDepth, tIncr, isoValue);";
    else if (property.compositingMode_.isSelectedIdentifier("ison"))
        compositingValue = "compositeISON(result, color, voxel.r, gradient, t, tDepth, isoValue);";

    shader.getFragmentShaderObject()->addShaderDefine(compositingKey, compositingValue);
}
void setShaderUniforms(Shader& shader, const SimpleRaycastingProperty& property) {
    shader.setUniform("samplingRate_", property.samplingRate_.get());
    shader.setUniform("isoValue_", property.isoValue_.get());
}

void setShaderUniforms(Shader& shader, const SimpleRaycastingProperty& property, std::string name) {
    shader.setUniform(name + ".samplingRate", property.samplingRate_.get());
    shader.setUniform(name + ".isoValue", property.isoValue_.get());
}

void addShaderDefinesBGPort(Shader& shader, ImageInport port) {
    std::string bgKey = "DRAW_BACKGROUND(result,t,tIncr,color,bgTDepth,tDepth)";
    if (port.isConnected()) {
        shader.getFragmentShaderObject()->addShaderDefine("HAS_BACKGROUND");
        shader.getFragmentShaderObject()->addShaderDefine(
            bgKey, "drawBackground(result,t,tIncr, texture(bgColor,texCoords),bgTDepth,tDepth);");
    } else {
        shader.getFragmentShaderObject()->removeShaderDefine("HAS_BACKGROUND");
        shader.getFragmentShaderObject()->addShaderDefine(bgKey, "result");
    }
}

void addShaderDefines(Shader& shader, const VolumeIndicatorProperty& property) {
    // compositing defines
    std::string key =
        "DRAW_PLANES(result, samplePosition, rayDirection, increment, params,t,tDepth)";
    std::string value = "result";

    if (property.enable_ &&
        (property.plane1_.enable_ || property.plane2_.enable_ || property.plane3_.enable_)) {
        std::string planes("");
        planes += property.plane1_.enable_ ? ", params.plane1" : "";
        planes += property.plane2_.enable_ ? ", params.plane2" : "";
        planes += property.plane3_.enable_ ? ", params.plane3" : "";
        value =
            "drawPlanes(result, samplePosition, rayDirection, increment " + planes + ",t,tDepth)";
    }
    shader.getFragmentShaderObject()->addShaderDefine(key, value);
}

void setShaderUniforms(Shader& shader, const VolumeIndicatorProperty& property, std::string name) {
    if (property.enable_) {
        if (property.plane1_.enable_) {
            shader.setUniform(name + ".plane1.position", property.plane1_.position_);
            shader.setUniform(name + ".plane1.normal", property.plane1_.normal_);
            shader.setUniform(name + ".plane1.color", property.plane1_.color_);
        }
        if (property.plane2_.enable_) {
            shader.setUniform(name + ".plane2.position", property.plane2_.position_);
            shader.setUniform(name + ".plane2.normal", property.plane2_.normal_);
            shader.setUniform(name + ".plane2.color", property.plane2_.color_);
        }
        if (property.plane3_.enable_) {
            shader.setUniform(name + ".plane3.position", property.plane3_.position_);
            shader.setUniform(name + ".plane3.normal", property.plane3_.normal_);
            shader.setUniform(name + ".plane3.color", property.plane3_.color_);
        }
    }
}

void addShaderDefines(Shader& shader, const StipplingProperty& property) {
    addShaderDefines(shader, property.mode_.get());
}

void addShaderDefines(Shader& shader, const StipplingProperty::Mode& mode) {
    std::string value;
    switch (mode) {
        case StipplingProperty::Mode::ScreenSpace:
            value = "1";
            break;
        case StipplingProperty::Mode::WorldSpace:
            value = "2";
            break;
        case StipplingProperty::Mode::None:
        default:
            break;
    }

    auto fragShader = shader.getFragmentShaderObject();
    if (mode != StipplingProperty::Mode::None) {
        fragShader->addShaderDefine("ENABLE_STIPPLING");
    } else {
        fragShader->removeShaderDefine("ENABLE_STIPPLING");
    }
    fragShader->addShaderDefine("STIPPLE_MODE", value);
}

void setShaderUniforms(Shader& shader, const StipplingProperty& property, std::string name) {
    shader.setUniform(name + ".length", property.length_.get());
    shader.setUniform(name + ".spacing", property.spacing_.get());
    shader.setUniform(name + ".offset", property.offset_.get());
    shader.setUniform(name + ".worldScale", property.worldScale_.get());
}

int getLogLineNumber(const std::string& compileLogLine) {
    int result = -1;
    std::istringstream input(compileLogLine);
    int num;

    if (input >> num) {
        char c;
        if (input >> c && c == '(') {
            if (input >> result) {
                return result;
            }
        }
    }

    // ATI parsing:
    // ATI error: "ERROR: 0:145: Call to undeclared function 'texelFetch'\n"
    std::vector<std::string> elems;
    std::stringstream ss(compileLogLine);
    std::string item;
    while (std::getline(ss, item, ':')) {
        elems.push_back(item);
    }
    if (elems.size() >= 3) {
        std::stringstream number;
        number << elems[2];
        number >> result;
    }

    return result;
}

std::string reformatInfoLog(
    const std::vector<std::pair<std::string, unsigned int> >& lineNumberResolver,
    const std::string compileLog) {

    std::ostringstream result;
    std::string curLine;
    std::istringstream origShaderInfoLog(compileLog);

    while (std::getline(origShaderInfoLog, curLine)) {
        if (!curLine.empty()) {
            int origLineNumber = getLogLineNumber(curLine);
            if (origLineNumber > 0) {
                auto lineNumber = lineNumberResolver[origLineNumber - 1].second;
                auto fileName = lineNumberResolver[origLineNumber - 1].first;
                result << "\n"
                       << fileName << " (" << lineNumber
                       << "): " << curLine.substr(curLine.find(":") + 1);
            } else {
                result << "\n" << curLine;
            }
        }
    }

    return result.str();
}

std::string getShaderInfoLog(GLuint id) {
    GLint maxLogLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLogLength);
    LGL_ERROR;

    if (maxLogLength > 1) {
        auto shaderInfoLog = util::make_unique<GLchar[]>(maxLogLength);
        GLsizei logLength{0};
        glGetShaderInfoLog(id, maxLogLength, &logLength, shaderInfoLog.get());
        return std::string(shaderInfoLog.get(), logLength);
    } else {
        return "";
    }
}

std::string getProgramInfoLog(GLuint id) {
    GLint maxLogLength;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLogLength);
    LGL_ERROR;

    if (maxLogLength > 1) {
        auto shaderInfoLog = util::make_unique<GLchar[]>(maxLogLength);
        GLsizei logLength{0};
        glGetProgramInfoLog(id, maxLogLength, &logLength, shaderInfoLog.get());
        return std::string(shaderInfoLog.get(), logLength);
    } else {
        return "";
    }
}

std::shared_ptr<const ShaderResource> findShaderResource(const std::string& fileName) {
    auto resource = ShaderManager::getPtr()->getShaderResource(fileName);
    if (!resource) {
        throw OpenGLException(
            "Shader file: " + fileName + " not found in shader search paths or shader resources.",
            IvwContextCustom("ShaderUtils"));
    }
    return resource;
}

}  // namespace utilgl

}  // namespace inviwo
