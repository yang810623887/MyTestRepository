#include "settings.h"

namespace inviwo {

	Settings::Settings(const std::string &id /*= ""*/)
		: identifier_(id)
		, isDeserializing_(false)
	{

	}

	Settings::~Settings()
	{

	}

	void Settings::addProperty(Property* property, bool owner /*= true*/)
	{
		PropertyOwner::addProperty(property, owner);
		//property->onChange(this, &Settings::save);
	}

	void Settings::addProperty(Property& property)
	{
		PropertyOwner::addProperty(&property, false);
		//property.onChange(this, &Settings::save);
	}

	std::string Settings::getIdentifier()
	{
		return identifier_;
	}

}