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


#include "AppEditorLogic.h"
// Editor logic, it takes effect only when the UnigineEditor is loaded.
// These methods are called right after corresponding editor script's (UnigineScript) methods.

AppEditorLogic::AppEditorLogic() {
	
}

AppEditorLogic::~AppEditorLogic() {
	
}

int AppEditorLogic::init() {
	// Write here code to be called on editor initialization.
	
	return 1;
}

// start of the main loop
int AppEditorLogic::update() {
	// Write here code to be called before updating each render frame when editor is loaded.
	
	return 1;
}

int AppEditorLogic::render() {
	// Write here code to be called before rendering each render frame when editor is loaded.
	
	return 1;
}
// end of the main loop

int AppEditorLogic::shutdown() {
	// Write here code to be called on editor shutdown.
	
	return 1;
}

int AppEditorLogic::destroy() {
	// Write here code to be called when the video mode is changed or the application is restarted (i.e. video_restart is called). It is used to reinitialize the graphics context.
	
	return 1;
}

int AppEditorLogic::worldInit() {
	// Write here code to be called on world initialization when editor is loaded.
	
	return 1;
}

int AppEditorLogic::worldShutdown() {
	// Write here code to be called on world shutdown when editor is loaded.
	
	return 1;
}

int AppEditorLogic::worldSave() {
	// Write here code to be called on world save when editor is loaded.
	
	return 1;
}