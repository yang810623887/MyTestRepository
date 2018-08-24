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
#include "UnigineApp.h"
#include "UnigineConsole.h"

#include "AppSystemLogic.h"
// System logic, it exists during the application life cycle.
// These methods are called right after corresponding system script's (UnigineScript) methods.

using namespace Unigine;
using namespace Unigine::Math;

AppSystemLogic::AppSystemLogic()
{
}

AppSystemLogic::~AppSystemLogic()
{
}

int AppSystemLogic::init() {
	// Write here code to be called on engine initialization.
	App::get()->setUpdate(1);
	Console::get()->run("world_load data/world_spline_graph");
	return 1;
}

// start of the main loop
int AppSystemLogic::update() {
	// Write here code to be called before updating each render frame.
	
	return 1;
}

int AppSystemLogic::render() {
	// Write here code to be called before rendering each render frame.
	
	return 1;
}
// end of the main loop

int AppSystemLogic::shutdown() {
	// Write here code to be called on engine shutdown.
	
	return 1;
}

int AppSystemLogic::destroy() {
	// Write here code to be called when the video mode is changed or the application is restarted (i.e. video_restart is called). It is used to reinitialize the graphics context.
	
	return 1;
}
