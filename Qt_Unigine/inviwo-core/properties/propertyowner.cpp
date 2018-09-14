#include "propertyowner.h"

namespace inviwo {

	PropertyOwner::PropertyOwner()
	{

	}

	PropertyOwner::PropertyOwner(const PropertyOwner& rhs)
	{

	}

	//PropertyOwner& PropertyOwner::operator=(const PropertyOwner& that)
	//{

	void PropertyOwner::addProperty(Property* property, bool owner /*= true*/)
	{
		/*if (getPropertyByIdentifier(property->getIdentifier()) != nullptr) {
			throw Exception(
				"Can't add property, identifier \"" + property->getIdentifier() + "\" already exist.",
				IvwContext);
		}
		if (auto parent = dynamic_cast<Property*>(this)) {
			if (parent == property) {
				throw Exception("Can't add property \"" + property->getIdentifier() + "\" to itself.",
					IvwContext);
			}
		}*/
		properties_.push_back(property);
		//property->setOwner(this);
	}

	void PropertyOwner::addProperty(Property& property)
	{
		addProperty(&property, false);
	}

	//}

	const std::vector<Property*>& PropertyOwner::getProperties() const
	{
		return properties_;
	}

}