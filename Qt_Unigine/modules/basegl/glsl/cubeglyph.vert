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

layout(location = 4) in uint in_PickId;
layout(location = 5) in float in_CubeSizes;

#include "utils/structs.glsl"

uniform GeometryParameters geometry;
uniform CameraParameters camera;

uniform vec4 customColor = vec4(1, 0, 0, 1);
uniform float customSize = 0.1f;

out vec4 worldPosition_;
out vec4 cubeColor_;
flat out float cubeSize_;
flat out uint pickID_;

void main(void) {
#if defined(UNIFORM_SIZE)
    cubeSize_ = customSize;
#else
    cubeSize_ = in_CubeSizes;
#endif  // UNIFORM_RADIUS

#if defined(UNIFORM_COLOR)
    cubeColor_ = customColor;
#else
    cubeColor_ = in_Color;
#endif // UNIFORM_COLOR

    worldPosition_ = geometry.dataToWorld * vec4(in_Vertex.xyz, 1.0);

    gl_Position = worldPosition_;

    pickID_ = in_PickId;
}
