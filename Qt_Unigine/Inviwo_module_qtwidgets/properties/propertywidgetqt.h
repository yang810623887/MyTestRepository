/*********************************************************************************
*
* NameSpace: Inviwo_module_qtwidgets
* ClassName: propertywidgetqt
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 14:27:55
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROPERTYWIDGETQT_H
#define IVW_PROPERTYWIDGETQT_H

#include "../qtwidgetsmoduledefine.h"
#include "../../inviwo-core/properties/propertyvisibility.h"
#include "../../inviwo-core/properties/propertywidget.h"
#include "../../inviwo-core/properties/propertyobserver.h"
#include "../../inviwo-core/properties/optionproperty.h"

#include <QWidget>


class QMenu;
class QAction;
class QActionGroup;

namespace inviwo {

	

	class PropertyListWidget; 
	class Property;
	class InviwoDockWidget;

 	class IVW_MODULE_QTWIDGETS_API PropertyWidgetQt : public QWidget,
 													  public PropertyWidget,
 													  public PropertyObserver
 	{
		Q_OBJECT
 	public:
		//using BaseCallBack = std::function<void()>;
		PropertyWidgetQt(Property* property = nullptr);
		virtual ~PropertyWidgetQt();

		// Should be called first thing after the property has been added to a layout.
		virtual void initState();

		static const int minimumWidth;
		static const int spacing;
		static const int margin;


		void setParentPropertyWidget(PropertyWidgetQt* parent, InviwoDockWidget* widget);

	signals:
		void updateSemantics(PropertyWidgetQt*);

	private:
		PropertyWidgetQt* parent_;
		InviwoDockWidget* baseContainer_;
 	};

}

#endif