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


#ifndef __GL_APP_QT_H__
#define __GL_APP_QT_H__

#include "AppQt.h"

#include "UnigineApp.h"
#include <UnigineEngine.h>

class IVW_UNIGINE_API GLAppQt : public AppQt
{
	Q_OBJECT

public:
	GLAppQt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~GLAppQt();

	virtual void *getHandle();
	virtual const char *getName();
};

#endif // __GL_APP_QT_H__
