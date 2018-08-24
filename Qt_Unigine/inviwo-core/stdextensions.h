/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: stdextensions
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 14:53:21
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_STDEXTENSIONS_H
#define IVW_STDEXTENSIONS_H
#include "inviwocoredefine.h"
#include <memory>
namespace inviwo {

	namespace util {


		template <typename T, typename std::enable_if<
			!std::is_abstract<T>::value && std::is_default_constructible<T>::value,
			int>::type = 0>
			T *defaultConstructType()
		{
			return new T();
		}

		template <typename T, typename std::enable_if<
			std::is_abstract<T>::value || !std::is_default_constructible<T>::value,
			int>::type = 0>
			T *defaultConstructType()
		{
			return nullptr;
		}

	}

}

#endif
