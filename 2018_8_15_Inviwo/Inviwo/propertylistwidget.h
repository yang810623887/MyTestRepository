#pragma once
#ifndef IVW_PROPERTYLISTWIDGET_H
#define IVW_PROPERTYLISTWIDGET_H
#include "InviwoDockWidget.h"

#include <QWidget>
#include <QEvent>

namespace inviwo {
	class PropertyListFrame : public QWidget
	{
	public:
		PropertyListFrame(QWidget* parent);
		~PropertyListFrame() = default;
		//virtual QSize sizeHint() const;
		//virtual QSize minimumSizeHint() const;
		//void paintEvent(QPaintEvent*);
	};
	class PropertyListWidget : public InviwoDockWidget {
		Q_OBJECT
	public:
		//typedef std::unordered_map<Processor*, CollapsibleGroupBoxWidgetQt*> WidgetMap;
		PropertyListWidget(QWidget* parent);
		~PropertyListWidget() = default;

	private:

	};
}

#endif

