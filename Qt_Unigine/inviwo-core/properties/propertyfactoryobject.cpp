#include "propertyfactoryobject.h"

namespace inviwo {

	PropertyFactoryObject::PropertyFactoryObject(const std::string& className)
		: className_(className){}

	PropertyFactoryObject::~PropertyFactoryObject(){}


	std::string PropertyFactoryObject::getClassIdentifier() const
	{
		return className_;
	}

}