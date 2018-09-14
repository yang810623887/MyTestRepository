#include "stringconversion.h"

#include <random>
#include <iomanip>

#if defined(__clang__) || defined(__GNUC__)
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

namespace inviwo {

	std::vector<std::string> splitString(const std::string& str, char delimeter)
	{
		std::vector<std::string> strings;
		std::stringstream stream(str);
		std::string part;

		while (std::getline(stream, part, delimeter))
		{
			strings.push_back(part);
		}
		return strings;
	}


	IVW_CORE_API std::string htmlEncode(const std::string& data)
	{
		std::string buffer;
		buffer.reserve(data.size());
		for (size_t pos = 0; pos != data.size(); ++pos)
		{
			switch (data[pos])
			{
			case '&':
				buffer.append("&amp;");
				break;
			case '\"':
				buffer.append("&quot;");
				break;
			case '\'':
				buffer.append("&apos;");
				break;
			case '<':
				buffer.append("&lt;");
				break;
			case '>':
				buffer.append("&gt;");
				break;
			default:
				buffer.append(&data[pos], 1);
				break;
			}
		}
		return buffer;
	}

	IVW_CORE_API std::vector<std::string> splitStringWithMultipleDelimiters(const std::string& str, std::vector<char> delimiters /*= std::vector<char>()*/)
	{
		if (!delimiters.size())
		{
			delimiters.push_back('_');
			delimiters.push_back('+');
			delimiters.push_back('-');
			delimiters.push_back('.');
			delimiters.push_back(' ');
		}

		std::string tempString = str;
		char lastDelimiter = delimiters[delimiters.size() - 1];

		for (size_t i = 0; i < delimiters.size() - 1; i++)
		{
			replaceInString(tempString, toString(delimiters[i]), toString(lastDelimiter));
		}
		return splitString(tempString, lastDelimiter);
	}

	IVW_CORE_API std::string removeFromString(std::string str, char char_to_remove /*= ' '*/)
	{
		str.erase(std::remove(str.begin(), str.end(), char_to_remove), str.end());
		return str;
	}

	IVW_CORE_API void replaceInString(std::string& str, const std::string& oldStr, const std::string& newStr)
	{
		size_t pos = 0;
		while ((pos = str.find(oldStr, pos)) != std::string::npos)
		{
			str.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
	}

	IVW_CORE_API std::string parseTypeIdName(std::string str)
	{
#if defined(__clang__) || defined(__GNUC__)
		struct handle {
			char* p;
			handle(char* ptr) : p(ptr) {}
			~handle() { std::free(p); }
		};
		const char* cstr = str.c_str();
		int status = -4;
		handle result(abi::__cxa_demangle(cstr, nullptr, nullptr, &status));
		if (status == 0) str = result.p;
#else
		replaceInString(str, "class", "");
		replaceInString(str, "const", "");
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64)
		replaceInString(str, "__ptr64", "");
#endif
#endif
		replaceInString(str, "inviwo::", "");
		return removeFromString(removeFromString(str, '*'), ' ');
	}

	IVW_CORE_API std::string toLower(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c)
			{
			return static_cast<unsigned char>(std::toupper(c));
			});
		return str;
	}

	// trim from start
	std::string ltrim(std::string s)
	{
		s.erase(s.begin(),
			std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	std::string rtrim(std::string s) {
		s.erase(
			std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			s.end());
		return s;
	}

	// trim from both ends
	std::string trim(std::string s) { return ltrim(rtrim(s)); }

}