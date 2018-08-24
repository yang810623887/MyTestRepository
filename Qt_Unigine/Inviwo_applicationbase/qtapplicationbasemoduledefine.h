/*********************************************************************************
*
* NameSpace: Inviwo_applicationbase
* ClassName: qtapplicationbasemoduledefine
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-22 11:09:39
* --------------------------------------------------------------------------------
* DateTime : 2018/08/22
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef _IVW_QTAPPLICATIONBASE_DEFINE_H_
#define _IVW_QTAPPLICATIONBASE_DEFINE_H_

#ifdef INVIWO_ALL_DYN_LINK //DYNAMIC
 // If we are building DLL files we must declare dllexport/dllimport
#ifdef IVW_QTAPPLICATIONBASE_EXPORTS
#ifdef _WIN32
#define IVW_QTAPPLICATIONBASE_API __declspec(dllexport)
#else //UNIX (GCC)
#define IVW_QTAPPLICATIONBASE_API __attribute__ ((visibility ("default")))
#endif
#else
#ifdef _WIN32
#define IVW_QTAPPLICATIONBASE_API __declspec(dllimport)
#else
#define IVW_QTAPPLICATIONBASE_API
#endif
#endif
#else //STATIC
#define IVW_QTAPPLICATIONBASE_API
#endif

#endif /* _IVW_QTAPPLICATIONBASE_DEFINE_H_ */
