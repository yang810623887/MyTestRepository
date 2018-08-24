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


#include "D3DTest.h"

D3D11AppQt::D3D11AppQt(QWidget *parent, int debug, Qt::WindowFlags flags)
	: UnigineWidget(parent, flags)
{
	context = initD3D11Context();
	setTitle("D3D11AppQt");
}

D3D11AppQt::~D3D11AppQt()
{
}

const char *D3D11AppQt::getName()
{
	return "direct3d11";
}
