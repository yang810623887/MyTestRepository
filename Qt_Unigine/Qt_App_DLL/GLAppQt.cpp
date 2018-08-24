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


#include "GLAppQt.h"

#ifdef _LINUX
#include <GL/glx.h>
#include <GL/glxext.h>
#endif

GLAppQt::GLAppQt(QWidget *parent, Qt::WindowFlags flags)
	: UnigineWidget(parent, flags)
{
	context = initGLContext();
	setTitle("GLAppQt");
}

GLAppQt::~GLAppQt()
{
}

void *GLAppQt::getHandle()
{
#ifdef _WIN32
	return (void *)winId();
#elif _LINUX
	static Window window;
	window = winId();
	return &window;
#endif
}

const char *GLAppQt::getName()
{
	return "opengl";
}
