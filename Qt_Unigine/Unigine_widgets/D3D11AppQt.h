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


#ifndef __D3D11_APP_QT_H__
#define __D3D11_APP_QT_H__

#include "AppQt.h"

#include <UnigineApp.h>
#include <UnigineEngine.h>



class IVW_UNIGINE_API D3D11AppQt : public AppQt
{
	Q_OBJECT

public:
	D3D11AppQt(QWidget *parent = 0, int debug = 0, Qt::WindowFlags flags = 0);
	virtual ~D3D11AppQt();

	virtual const char *getName();
};

#endif // __D3D11_APP_QT_H__
