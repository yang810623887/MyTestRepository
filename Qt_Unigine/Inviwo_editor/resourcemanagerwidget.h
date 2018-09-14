/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: resourcemanagerwidget
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-29 14:31:52
* --------------------------------------------------------------------------------
* DateTime : 2018/08/29
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_RESOURCE_MANAGER_WIDGET_H
#define IVW_RESOURCE_MANAGER_WIDGET_H

#include "inviwoqteditordefine.h"
#include "InviwoDockWidget.h"

namespace inviwo {
	class IVW_QTEDITOR_API ResourceManagerWidget : public InviwoDockWidget
	{
		Q_OBJECT
	public:
		ResourceManagerWidget(QWidget* parent);
		~ResourceManagerWidget();
	};

}
#endif

