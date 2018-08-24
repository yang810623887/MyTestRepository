/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: exception
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 14:12:26
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_EXCEPTION_H
#define IVW_EXCEPTION_H

#include "inviwocoredefine.h"

#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include <vector>

namespace inviwo {

//	struct IVW_CORE_API ExceptionContext
//	{
//		ExceptionContext(std::string caller = "", std::string file = "", std::string function = "", int line = 0);
//		const std::string& getCaller();
//		const std::string& getFile();
//		const std::string& getFunction();
//		const int& getLine();
//
//	private:
//		std::string caller_;
//		std::string file_;
//		std::string function_;
//		int line_;
//	};
//#define IvwContext  \
//	ExceptionContext(parseTypeIdName(std::string(typeid(this).name())), std::string(__FILE__),\
//		std::string(__FUNCTION__), __LINE__);
//
////结构体内容的初始化
//#define IvwContextCustom(source) \
//    ExceptionContext(source, std::string(__FILE__), std::string(__FUNCTION__), __LINE__)
//
//	class IVW_CORE_API Exception : public std::exception
//	{
//	public: 
//		Exception(const std::string& message = "", ExceptionContext context = ExceptionContext());
//		virtual ~Exception() throw();
//		virtual std::string getMessage() const throw();
//		virtual const char* what() const throw() override;
//		virtual const ExceptionContext& getContext() const;
//
//	private:
//		std::string message_; //"Singleton already initialized"
//		ExceptionContext context_; //有值
//	};
}

#endif