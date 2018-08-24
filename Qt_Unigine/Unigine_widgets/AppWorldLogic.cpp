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


#include "AppWorldLogic.h"
// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

AppWorldLogic::AppWorldLogic() {
	
}

AppWorldLogic::~AppWorldLogic() {
	
}

int AppWorldLogic::init() {
	// Write here code to be called on world initialization: initialize resources for your world scene during the world start.
	
	// create player
	PlayerSpectatorPtr player = PlayerSpectator::create();
	player->release();
	player->setPosition(Vec3(3.0f));
	player->setDirection(vec3(-1.0f), vec3(0.0f, 0.0f, -1.0f));
	Game::get()->setPlayer(player->getPlayer());

	// create light
	//light = LightWorld::create(vec4::WHITE);
	light_0 = LightOmni::create(vec4(1.0f, 0.0f, 0.0f, 1.0f), 100.0f, "");
	light_1 = LightOmni::create(vec4(0.0f, 1.0f, 0.0f, 1.0f), 100.0f, "");
	light_2 = LightOmni::create(vec4(0.0f, 0.0f, 1.0f, 1.0f), 100.0f, "");

	// create meshes
	ObjectMeshStaticPtr mesh_0 = ObjectMeshStatic::create("resources/cbox.mesh");
	mesh_0->release();
	mesh_0->setTransform(translate(Vec3(-2.0f, 0.0f, 0.0f)));
	mesh_0->setMaterial("mesh_base", "*");
	
	// create WorldSplineGraph
	node = WorldSplineGraph::create();

	// load spline data
	int ref = node->load("resources/spline.spl");

	ref = ref + 1;
	// set geometry and forward axis
	node->addSourceNode("resources/road_hi_poly.node", WorldSplineGraph::FORWARD_X);

	// assign all segments to added geometry
	// SEGMENT_STRETCH - for stretching single node by segment
	// SEGMENT_TILING - for tiling nodes above segment
	for (int i = 0; i < node->getNumSegments(); i++)
	{
		node->assignSegmentSource(i, 0, WorldSplineGraph::SEGMENT_STRETCH);
	}
		
	return 1;
}

// start of the main loop
int AppWorldLogic::update() {
	// Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.
	Game *game = Game::get();
	float time = game->getTime();
	float angle_0 = time * 1.0f;
	float angle_1 = time * 1.5f;
	float angle_2 = time * 2.0f;
	light_0->setWorldTransform(translate(UNIGINE_VEC3(sinf(angle_0), cosf(angle_0), 1.0f) * 20.0f));
	light_1->setWorldTransform(translate(UNIGINE_VEC3(sinf(angle_1), cosf(angle_1), 1.0f) * 20.0f));
	light_2->setWorldTransform(translate(UNIGINE_VEC3(sinf(angle_2), cosf(angle_2), 1.0f) * 20.0f));
	return 1;
}

int AppWorldLogic::render() {
	// The engine calls this function before rendering each render frame: correct behavior after the state of the node has been updated.
	
	return 1;
}

int AppWorldLogic::flush() {
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls flush() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	
	return 1;
}
// end of the main loop

int AppWorldLogic::shutdown() {
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	
	return 1;
}

int AppWorldLogic::destroy() {
	// Write here code to be called when the video mode is changed or the application is restarted (i.e. video_restart is called). It is used to reinitialize the graphics context.
	
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream) {
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream) {
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	
	UNIGINE_UNUSED(stream);
	return 1;
}
