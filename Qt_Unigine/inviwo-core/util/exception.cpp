#include "exception.h"
//#include <logcentral.h>
namespace inviwo {

	

	Exception::Exception(const std::string& message /*= ""*/, ExceptionContext context /*= ExceptionContext()*/)
		: std::exception(), message_(message), context_(context){}

	Exception::~Exception() throw(){}

	std::string Exception::getMessage() const throw()
	{
		return message_;
	}

	const char* Exception::what() const throw()
	{
		return message_.c_str();
	}

	const ExceptionContext& Exception::getContext() const
	{
		return context_;
	}

	RangeException::RangeException(const std::string& message /*= ""*/, ExceptionContext context /*= ExceptionContext()*/)
		: Exception(message, context){}

	NullPointerException::NullPointerException(const std::string& message /*= ""*/, ExceptionContext context /*= ExceptionContext()*/)
		: Exception(message, context) {}

	IgnoreException::IgnoreException(const std::string& message, ExceptionContext context)
		: Exception(message, context) {}

	AbortException::AbortException(const std::string& message, ExceptionContext context)
		: Exception(message, context) {}

	FileException::FileException(const std::string& message, ExceptionContext context)
		: Exception(message, context) {}


	ModuleInitException::ModuleInitException(const std::string& message
											  ,ExceptionContext context
											  ,std::vector<std::string> modulesToDeregister)
		: Exception(message, context)
		, modulesToDeregister_(std::move(modulesToDeregister)){}

	const std::vector<std::string>& ModuleInitException::getModulesToDeregister() const {
		return modulesToDeregister_;
	}
	void StandardExceptionHandler::operator()(ExceptionContext context) {
		//try {
		//	throw;
		//}
		//catch (Exception& e) {
		//	util::log(e.getContext(), e.getMessage(), LogLevel::Error);
		//}
		//catch (std::exception& e) {
		//	util::log(context, std::string(e.what()), LogLevel::Error);
		//}
		//catch (...) {
		//	util::log(context, "Unknown error", LogLevel::Error);
		}
	


	ExceptionContext::ExceptionContext(std::string caller, std::string file, std::string function, int line)
		: caller_(caller)
		, file_(file)
		, function_(function)
		, line_(line)
	{
		
	}
	const std::string& ExceptionContext::getCaller() { return caller_; }

	const std::string& ExceptionContext::getFile() { return file_; }

	const std::string& ExceptionContext::getFunction() { return function_; }

	const int& ExceptionContext::getLine() { return line_; }

}