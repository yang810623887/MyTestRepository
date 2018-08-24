#pragma once

#ifndef IVW_PROPERTYWIDGETQT_H
#define IVW_PROPERTYWIDGETQT_H

#include <QWidget>

namespace inviwo {

	class Property;

	class PropertyWidgetQt : public QWidget
	{
		Q_OBJECT
	public:

		using BaseCallBack = std::function<void()>;

		PropertyWidgetQt(Property* property = nullptr);
		virtual ~PropertyWidgetQt();

	};

}

#endif