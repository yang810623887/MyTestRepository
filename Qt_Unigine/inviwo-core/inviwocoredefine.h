/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: inviwocoredefine
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-23 14:06:14
* --------------------------------------------------------------------------------
* DateTime : 2018/08/23
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef _IVW_CORE_DEFINE_H_
#define _IVW_CORE_DEFINE_H_

#ifdef INVIWO_ALL_DYN_LINK //DYNAMIC
 // If we are building DLL files we must declare dllexport/dllimport
#ifdef IVW_CORE_EXPORTS
#ifdef _WIN32
#define IVW_CORE_API __declspec(dllexport)
#define IVW_CORE_EXT
#else //UNIX (GCC)
#define IVW_CORE_API __attribute__ ((visibility ("default")))
#define IVW_CORE_EXT
#endif
#else
#ifdef _WIN32
#define IVW_CORE_API __declspec(dllimport)
#define IVW_CORE_EXT extern
#else
#define IVW_CORE_API
#define IVW_CORE_EXT extern
#endif
#endif
#else //STATIC
#define IVW_CORE_API
#define IVW_CORE_EXT extern
#endif

#endif /* _IVW_CORE_DEFINE_H_ */