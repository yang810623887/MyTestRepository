/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: stringconversion
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 15:28:37
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_STRINGCONVERSION_H
#define IVW_STRINGCONVERSION_H
#include "inviwocoredefine.h"
#include <algorithm>
#include <string>
#include <vector>

namespace inviwo {

	template <class T>
	std::string toString(T value)
	{
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}

	template <class T>
	T stringTo(const std::string& str)
	{
		T result;
		std::istringstream stream;
		stream.str(str);
		stream >> result;
		return result;
	}

	IVW_CORE_API std::vector<std::string> splitString(const std::string& str, char delimeter = ' ');

	template <typename T>
	std::string joinString(const std::vector<T>& str, std::string delimeter = " ");
	{
		std::stringstream ss;
		std::copy(str.begin(), str.end(), util::make_ostream_joiner(ss, delimater));
	}
}
#endif