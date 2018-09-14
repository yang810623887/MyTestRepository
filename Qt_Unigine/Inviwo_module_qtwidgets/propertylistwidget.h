#pragma once
#ifndef IVW_PROPERTYLISTWIDGET_H
#define IVW_PROPERTYLISTWIDGET_H
#include "InviwoDockWidget.h"
#include "qtwidgetsmoduledefine.h"

#include <QWidget>
#include <QEvent>
#include <unordered_map>

class QVBoxLayout;
class QScrollArea;

namespace inviwo {

	class CollapsibleGroupBoxWidgetQt;

	class IVW_MODULE_QTWIDGETS_API PropertyListFrame : public QWidget
	{
	public:
		PropertyListFrame(QWidget* parent);
		~PropertyListFrame() = default;
		virtual QSize sizeHint() const;
		virtual QSize minimumSizeHint() const;
		void paintEvent(QPaintEvent*);
	};
	class IVW_MODULE_QTWIDGETS_API PropertyListWidget : public InviwoDockWidget {
		Q_OBJECT
	public:
	//	typedef std::unordered_map<Processor*, CollapsibleGroupBoxWidgetQt*> WidgetMap;


		PropertyListWidget(QWidget* parent);
		~PropertyListWidget() = default;

	private:
		QScrollArea* scrollArea_;

	private:

	};
}

#endif

