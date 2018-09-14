#include "resourcemanagerwidget.h"


namespace inviwo {

	ResourceManagerWidget::ResourceManagerWidget(QWidget* parent)
		: InviwoDockWidget(tr("Resources"), parent)
	{
		setObjectName("ResourceManagerWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	}

	ResourceManagerWidget::~ResourceManagerWidget()
	{

	}

}
