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
#include "../inviwocoredefine.h"
#include "ostreamjoiner.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <functional>
#include <cctype>
#include <locale>

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
	std::string joinString(const std::vector<T>& str, std::string delimeter = " ")
	{
		std::stringstream ss;
		std::copy(str.begin(), str.end(), util::make_ostream_joiner(ss, delimater));
		return ss.str();
	}

	template <typename Iterator>
	std::string joinString(Iterator begin, Iterator end, std::string delimeter = " ")
	{
		std::stringstream ss;
		std::copy(begin, end, util::make_ostream_joiner(ss, delimeter));
		return ss.str();
	}

	IVW_CORE_API std::string htmlEncode(const std::string& data);

	IVW_CORE_API std::vector<std::string> splitStringWithMultipleDelimiters(const std::string& str, std::vector<char> delimiters = std::vector<char>());

	IVW_CORE_API std::string removeSubString(const std::string& str, const std::string& strToRemove);

	IVW_CORE_API std::string removeFromString(std::string str, char char_to_remove = ' ');

	IVW_CORE_API void replaceInString(std::string& str, const std::string& oldStr, const std::string& newStr);

	IVW_CORE_API std::string parseTypeIdName(std::string str);

	IVW_CORE_API std::string toUpper(std::string str);

	IVW_CORE_API std::string toLower(std::string str);

	IVW_CORE_API size_t countLines(std::string str);

	IVW_CORE_API std::string randomString(size_t length = 10);

	// trim from start
	IVW_CORE_API std::string ltrim(std::string s);
	// trim from end
	IVW_CORE_API std::string rtrim(std::string s);
	// trim from both ends
	IVW_CORE_API std::string trim(std::string s);

	IVW_CORE_API std::string dotSeperatedToPascalCase(const std::string& s);
	IVW_CORE_API std::string camelCaseToHeader(const std::string& s);

	/**
	* \brief convert the given duration from milliseconds to a string.
	* The returned string will have the format "%dd %dh %dmin %dsec %.3fms", where days, hours,
	* minutes, seconds, ... are suppressed up to the first non-zero unit if not needed. Milliseconds
	* and seconds are combined if larger than 1 second.
	*
	* @param ms  in milliseconds
	* @param includeZeros   if true, time units for zero values are always shown, e.g.
	*                       "2d 0h 0min 23s" vs. "2d 23s" and "2h 0min 0s" vs. "2h"
	* @param spacing   if true, a space is inserted between digits and units
	* @return duration formatted as string
	*/
	IVW_CORE_API std::string msToString(double ms, bool includeZeros = true, bool spacing = false);

	template<class Rep, class Period = std::ratio<1>>
	std::string durationToString(std::chrono::duration<Rep, Period> duration, bool includeZeros = true, bool spacing = false)
	{
		using milliseconds = std::chrono::duration<double, std::milli>;
		auto ms = std::chrono::duration_cast<milliseconds>(duration, includeZeros, spacing);
		return msToString(ms.count());
	}
}

#endif