#include "propertywidget.h"

namespace inviwo {

	PropertyWidget::PropertyWidget() = default;

	PropertyWidget::PropertyWidget(Property* property)
		: property_(property){}

	Property* inviwo::PropertyWidget::getProperty()
	{
		return property_;
	}



	

}