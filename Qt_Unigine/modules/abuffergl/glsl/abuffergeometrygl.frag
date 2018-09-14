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

#include "abuffer.hglsl"

#include "utils/shading.glsl"

uniform LightParameters lighting;
uniform CameraParameters camera;

in vec4 worldPosition_;
in vec3 normal_;
in vec3 viewNormal_;
in vec3 texCoord_;
in vec4 color_;

uniform float globalTransparency_;

void main() {
    vec4 fragColor = vec4(1.0);
    vec3 toCameraDir_ = camera.position - worldPosition_.xyz;
    fragColor.rgb = APPLY_LIGHTING(lighting, color_.rgb, color_.rgb, vec3(1.0f), worldPosition_.xyz,
                                   normalize(normal_), normalize(toCameraDir_));

    PickingData = vec4(0, 0, 0, 0);
    FragData0 = fragColor;

#if (USE_ABUFFER == 1)
    u8vec4 abufferFrag = u8vec4(FragData0.xyz * 255.0, (color_.a*globalTransparency_) * 255.0);
    abufferFrag = clamp(abufferFrag, u8vec4(0), u8vec4(255));
    buildABufferLinkList(ivec2(gl_FragCoord.x, gl_FragCoord.y),
                         abufferFrag,
                         gl_FragCoord.z);
#endif
}
