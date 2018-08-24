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


#include <core/shaders/common/fragment.h>

INIT_TEXTURE(0, TEX_DEPTH)
INIT_TEXTURE(1, TEX_ALBEDO)
INIT_TEXTURE(2, TEX_NORMAL)
INIT_TEXTURE(3, TEX_SHADING)
INIT_TEXTURE(4, TEX_BENT_NORMAL)
INIT_TEXTURE(5, TEX_SSAO)

MAIN_BEGIN(FRAGMENT_OUT, FRAGMENT_IN)
	
	float2 uv = IN_POSITION.xy * s_viewport.zw;
	
	OUT_COLOR = float4_one;
	
	// Calculate border mask
	float native_depth = TEXTURE_BIAS_ZERO(TEX_DEPTH, uv).r;
	float clear = sign(abs(native_depth));
	
	float4 clear_color = float4_zero;
	
	GBuffer gbuffer = GBufferDefault();
	
	#ifdef GRAB_MODE_ALBEDO
		loadGBufferAlbedo(gbuffer, TEXTURE_OUT(TEX_ALBEDO), uv);
		OUT_COLOR.rgb = gbuffer.albedo;
	#elif GRAB_MODE_NORMAL
		loadGBufferNormal(gbuffer, TEXTURE_OUT(TEX_NORMAL), uv);
		OUT_COLOR.rgb = gbuffer.normal * 0.5f + 0.5f;
		clear_color = float4(0.5f, 0.5f, 1.0f, 1.0f);
	#elif GRAB_MODE_BENT_NORMAL
		float3 normal = TEXTURE_BIAS_ZERO(TEX_BENT_NORMAL, uv).xyz * 2.0f - 1.0f;
		OUT_COLOR.rgb = normal * 0.5f + 0.5f;
		clear_color = float4(0.5f, 0.5f, 1.0f, 1.0f);
	#elif GRAB_MODE_SHADING
		loadGBufferNormal(gbuffer, TEXTURE_OUT(TEX_NORMAL), uv);
		loadGBufferShading(gbuffer, TEXTURE_OUT(TEX_SHADING), uv);
		OUT_COLOR.r = gbuffer.metalness;
		OUT_COLOR.g = gbuffer.roughness;
		OUT_COLOR.b = gbuffer.f0;
		OUT_COLOR.a = gbuffer.microfiber;
	#elif GRAB_MODE_AO
		loadGBufferAlbedo(gbuffer, TEXTURE_OUT(TEX_ALBEDO), uv);
		OUT_COLOR.r = gbuffer.occlusion;
	#elif GRAB_MODE_SSAO
		float ssao = TEXTURE_BIAS_ZERO(TEX_SSAO, uv).r;
		OUT_COLOR.r = ssao;
	#elif GRAB_MODE_TRANSLUCENCE
		loadGBufferShading(gbuffer, TEXTURE_OUT(TEX_SHADING), uv);
		OUT_COLOR.r = gbuffer.translucent;
	#endif
	
	OUT_COLOR = lerp(clear_color, OUT_COLOR, clear);
	
MAIN_END
