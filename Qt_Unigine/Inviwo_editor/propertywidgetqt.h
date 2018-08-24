#pragma once

#ifndef IVW_PROPERTYWIDGETQT_H
#define IVW_PROPERTYWIDGETQT_H

#include <QWidget>
#include "inviwoqteditordefine.h"

namespace inviwo {

	class Property;

	class IVW_QTEDITOR_API PropertyWidgetQt : public QWidget
	{
		Q_OBJECT
	public:

//		using BaseCallBack = std::function<void()>;

		PropertyWidgetQt(Property* property = nullptr);
		virtual ~PropertyWidgetQt();

	};

}

#endif