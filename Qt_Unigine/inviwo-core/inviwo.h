/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: inviwo
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 16:04:46
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_INVIWO_H
#define IVW_INVIWO_H

#if defined(__clang__) || defined(__GNUC__) // sets NDEBUG when not debugging
	#ifndef NDEBUG
		#ifndef IVW_DEBUG
			#define IVW_DEBUG
		#endif
	#endif
#endif

#ifdef _MSC_VER
	#ifdef _DEBUG /// MVS sets _DEBUG when debugging
		#ifndef IVW_DEBUG
			#define IVW_DEBUG	
		#endif
	#endif
#endif
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdio.h>

#include "../build/_generated/inviwocommondefines.h"

//include glm
#include "glm.h"

#include "util/formats.h"

//error handling
#include "util/assertion.h"
#include "util/exception.h"
#include "util/logcentral.h"

#define IVW_UNUSED_PARAM(param) (void)param

//#define IVW_UNUSED_PARAM(param) (void)param
#include "io/serialization/serialization.h"

#if defined(IVW_DEPRECATION_WARNINGS)
#define ivwDeprecatedMethod(newFunction) \
    std::cout << __FUNCTION__ << " is deprecated. Use " << newFunction << " instead." << std::endl; \
    std::cout << "(" << __FILE__ << " - Line " << __LINE__ << ")." << std::endl;
#else
#define ivwDeprecatedMethod(newFunction)
#endif

#ifdef _MSC_VER
#ifdef IVW_ENABLE_MSVC_MEM_LEAK_TEST
#include <ext/vld/vld.h>
#endif
#endif

#endif