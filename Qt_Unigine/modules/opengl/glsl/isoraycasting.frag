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

#include "utils/structs.glsl"
#include "utils/sampler2d.glsl"
#include "utils/sampler3d.glsl"

#include "utils/classification.glsl"
#include "utils/compositing.glsl"
#include "utils/depth.glsl"
#include "utils/gradients.glsl"
#include "utils/shading.glsl"
#include "utils/raycastgeometry.glsl"

uniform sampler3D volume;
uniform VolumeParameters volumeParameters;

uniform sampler2D entryColor;
uniform sampler2D entryDepth;
uniform sampler2D entryPicking;
uniform ImageParameters entryParameters;

uniform sampler2D exitColor;
uniform sampler2D exitDepth;
uniform ImageParameters exitParameters;

uniform ImageParameters bgParameters;
uniform sampler2D bgColor;
uniform sampler2D bgPicking;
uniform sampler2D bgDepth;

uniform ImageParameters outportParameters;

uniform LightParameters lighting;
uniform CameraParameters camera;
uniform RaycastingParameters raycasting;

uniform int channel;

uniform vec4 surfaceColor = vec4(1);

#define ERT_THRESHOLD 0.95  // set threshold for early ray termination

vec4 rayTraversal(vec3 entryPoint, vec3 exitPoint, vec2 texCoords) {
    vec4 result = vec4(0.0);
    vec3 rayDirection = exitPoint - entryPoint;
    float tEnd = length(rayDirection);
    float tIncr =
        min(tEnd,
            tEnd / (raycasting.samplingRate * length(rayDirection * volumeParameters.dimensions)));
    float samples = ceil(tEnd / tIncr);
    tIncr = tEnd / samples;
    float t = 0.5f * tIncr;
    rayDirection = normalize(rayDirection);
    float tDepth = -1.0;
    vec4 color;
    vec4 voxel;
    vec3 samplePos;
    vec3 gradient;
    float prevS = 0;

    if (t >= tEnd) {
        gl_FragDepth = tDepth;
        return result;
    }

    samplePos = entryPoint + t * rayDirection;
    bool outside =
        getNormalizedVoxelChannel(volume, volumeParameters, samplePos,channel) < raycasting.isoValue;
    t += tIncr;
    vec3 toCameraDir =
        normalize(camera.position - (volumeParameters.textureToWorld * vec4(entryPoint, 1.0)).xyz);
    int stop = 1000;
    while (t < tEnd && stop-- > 0) {
        samplePos = entryPoint + t * rayDirection;
        voxel = getNormalizedVoxel(volume, volumeParameters, samplePos);

        float diff = voxel[channel] - raycasting.isoValue;
        bool sampOutside = voxel[channel] < raycasting.isoValue;
        float th = 0.001;
        if (abs(diff) < th) {  // close enough to the surface
            gradient =
                COMPUTE_GRADIENT_FOR_CHANNEL(voxel, volume, volumeParameters, samplePos, channel);
            gradient = normalize(gradient);

            // World space position
            vec3 worldSpacePosition = (volumeParameters.textureToWorld * vec4(samplePos, 1.0)).xyz;
            // Note that the gradient is reversed since we define the normal of a surface as
            // the direction towards a lower intensity medium (gradient points in the inreasing
            // direction)
            result.rgb = APPLY_LIGHTING(lighting, surfaceColor.rgb, surfaceColor.rgb, vec3(1.0),
                                        worldSpacePosition, -gradient, toCameraDir);
            result.a = 1.0;
            tDepth = t;
            t += tEnd;
            break;
        } else if (sampOutside != outside) {
            t -= tIncr;
            tIncr /= 2.0;
        }
        // early ray termination
        if (result.a > ERT_THRESHOLD) {
            t = tEnd;
        } else {
            t += tIncr;
        }
    }

    if (tDepth != -1.0) {
        tDepth = calculateDepthValue(camera, tDepth / tEnd, texture(entryDepth, texCoords).x,
                                     texture(exitDepth, texCoords).x);
    } else {
        tDepth = 1.0;
    }

#ifdef HAS_BACKGROUND
    {
        float d = texture(bgDepth, texCoords).x;
        if (tDepth == 1 || d < tDepth) {
            result = vec4(0);
            result = drawBackground(texture(bgColor, texCoords), 0, 0, result, 0, tDepth);
            tDepth = d;
        }
    }
#endif

    gl_FragDepth = tDepth;
    return result;
}

void main() {
    vec2 texCoords = gl_FragCoord.xy * outportParameters.reciprocalDimensions;
    vec3 entryPoint = texture(entryColor, texCoords).rgb;
    vec3 exitPoint = texture(exitColor, texCoords).rgb;

    vec4 color = vec4(0);

#ifdef HAS_BACKGROUND
    color = texture(bgColor, texCoords);
    gl_FragDepth = texture(bgDepth, texCoords).x;
    PickingData = texture(bgPicking, texCoords);
#else
    PickingData = vec4(0);
    if (entryPoint == exitPoint) {
        discard;
    }
#endif
    if (entryPoint != exitPoint) {
        color = rayTraversal(entryPoint, exitPoint, texCoords);
    }

    FragData0 = color;
}
