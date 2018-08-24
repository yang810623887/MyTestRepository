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


#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include "uniginewidgetdefine.h"

#include <UnigineConsole.h>
#include <UnigineEngine.h>
#include <UniginePlayers.h>
#include <UnigineGame.h>
#include <UnigineLights.h>
#include <UnigineApp.h>
#include <UnigineWorlds.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Unigine::Math;

class IVW_UNIGINE_API AppWorldLogic : public Unigine::WorldLogic {
	
public:
	AppWorldLogic();
	virtual ~AppWorldLogic();
	
	virtual int init();
	
	virtual int update();
	virtual int render();
	virtual int flush();
	
	virtual int shutdown();
	virtual int destroy();
	
	virtual int save(const Unigine::StreamPtr &stream);
	virtual int restore(const Unigine::StreamPtr &stream);

private:
	WorldSplineGraphPtr node;
	LightWorldPtr light;
	LightOmniPtr light_0;
	LightOmniPtr light_1;
	LightOmniPtr light_2;
};

#endif // __APP_WORLD_LOGIC_H__
