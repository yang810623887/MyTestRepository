/* Copyright (C) 2005-2018, UNIGINE Corp. All rights reserved.
 *
 * This file is a part of the UNIGINE 2.7.1 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE Corp. at http://unigine.com/
 */


#include <core/shaders/mesh/common/common.h>
#include <core/shaders/mesh/common/fragment.h>

INIT_TEXTURE(0, TEX_BACKGROUND)
INIT_TEXTURE(1, TEX_FOREGROUND)
INIT_TEXTURE(2, TEX_MASK)

MAIN_BEGIN(FRAGMENT_OUT, FRAGMENT_IN)
	
	float4 bg = TEXTURE_BIAS_ZERO(TEX_BACKGROUND, IN_UV);
	float4 fg = TEXTURE_BIAS_ZERO(TEX_FOREGROUND, IN_UV);
	float4 mask = TEXTURE_BIAS_ZERO(TEX_MASK, IN_UV);
	
	OUT_COLOR.rgb = lerp(bg.rgb, fg.rgb, mask.r);
	OUT_COLOR.a = 1.0f;
	
MAIN_END
