#include "property.h"


namespace inviwo {


	void inviwo::Property::propertyModified()
	{

	}

	const std::vector<PropertyWidget*>& Property::getWidgets() const
	{
		return propertyWidgets_;
	}

}
