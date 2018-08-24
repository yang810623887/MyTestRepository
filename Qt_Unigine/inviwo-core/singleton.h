/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: singleton
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 14:01:49
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_SINGLETON_H
#define IVW_SINGLETON_H

#include "exception.h"

namespace inviwo {

	//class SingletonException : public Exception {
	//public:

	//	//构造函数初始化列表初始化父类的构造函数
	//	SingletonException(const std::string& message = "",
	//		ExceptionContext context = ExceptionContext())
	//		: Exception(message, context) {}
	//};

	//template <class T>
	//class Singleton {
	//public:
	//	Singleton<T>() {};
	//	Singleton<T>(Singleton<T> const&) = delete;
	//	void operate = (Singleton<T> const&) = delete;

	//	static void init()
	//	{
	//		if (instance_ != nullptr)
	//		{
	//			throw SingletonException("Singleton already initialized", IvwContextCustom("Singleton"));
	//		}
	//		instance_ = util::defaultConstructType<T>();
	//		if (instance_ == nullptr)
	//		{
	//			throw SingletonException("Was not able to initialize singleton", IvwContextCustom("Singleton"));
	//		}
	//	}

	//	static void init(T* instance) {
	//		if (instance_ != nullptr) {
	//			throw SingletonException("Singleton already initialized", IvwContextCustom("Singleton"));
	//		}
	//		if (instance == nullptr) {
	//			throw SingletonException("Null pointer passed", IvwContextCustom("Singleton"));
	//		}
	//		instance_ = instance;
	//	};

	//	static T* getPtr() {
	//		if (instance_ == 0) {
	//			throw SingletonException(
	//				"Singleton not initialized. Ensure that init() is called in a thread-safe "
	//				"environment. ",
	//				IvwContextCustom("Singleton"));
	//		}
	//		return instance_;
	//	};

	//	static void deleteInstance() {
	//		delete instance_;
	//		instance_ = nullptr;
	//	};

	//	virtual ~Singleton() { Singleton<T>::resetInstance(); };

	//private:
	//	static void resetInstance() { instance_ = nullptr; };

	//	static T* instance_;
	//};

	//template <class T>
	//T* Singleton<T>::instance_ = nullptr;
}



#endif