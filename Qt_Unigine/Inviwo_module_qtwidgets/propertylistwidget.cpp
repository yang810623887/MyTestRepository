#include "propertylistwidget.h"



namespace inviwo {
	PropertyListFrame::PropertyListFrame(QWidget * parent)
		: QWidget(parent)
	{
		QSizePolicy sp(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
		sp.setVerticalStretch(0);
		sp.setHorizontalStretch(1);
		QWidget::setSizePolicy(sp);
	}

	PropertyListWidget::PropertyListWidget(QWidget* parent)
		: InviwoDockWidget(tr("Properties"), parent)
	{
		setObjectName("ProcessorListWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	}

}
