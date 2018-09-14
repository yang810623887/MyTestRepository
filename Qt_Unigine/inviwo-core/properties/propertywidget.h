/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: propertywidget
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 14:34:05
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROPERTYWIDGET_H
#define IVW_PROPERTYWIDGET_H
#include "../inviwocoredefine.h"

namespace inviwo {

	class Property;
	class IVW_CORE_API PropertyWidget
	{
	public:
		PropertyWidget();
		PropertyWidget(Property* property);
		~PropertyWidget() = default;

		virtual Property* getProperty();

	protected:
		Property* property_ = nullptr;  //< Non owning reference, can be null
	};


}
#endif