#include "inviwomodulefactoryobject.h"

namespace inviwo {

	inviwo::InviwoModuleFactoryObject::InviwoModuleFactoryObject(const std::string& name, 
																const std::string& description, 
																std::vector<std::string> depends)
		: name_(name)
		, description_(description)
		, depends_(depends){}

	InviwoModuleFactoryObject::~InviwoModuleFactoryObject()
	{

	}

}
