/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: property
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 14:41:21
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROPERTY_H
#define IVW_PROPERTY_H

#include "../inviwocoredefine.h"
#include "propertyobserver.h"
#include "propertyvisibility.h"
#include "propertywidget.h"
#include "invalidationlevel.h"

#include <functional>

namespace inviwo {

//#define InviwoPropertyInfo()
//	virtual std::string getClassIdentifier() const override { return CLASS_IDENTIFIER; }

//	static const std::string CLASS_IDENTIFIER

	class IVW_CORE_API Property : public PropertyObservable
	{
	public:


		virtual void propertyModified();


		/**
		* \brief Enable or disable editing of property
		*/
		/*virtual void setReadOnly(const bool& value);
		virtual bool getReadOnly() const;*/

		const std::vector<PropertyWidget*>& getWidgets() const;

	private:
		//ValueWrapper<bool> readOnly_;
		std::vector<PropertyWidget*> propertyWidgets_;
	};

}
/*class IVW_CORE_API Property */


#endif
