#include "helpwidget.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QTextBrowser>

namespace inviwo {
	HelpWidget::HelpWidget(InviwoMainWindow * mainwindow)
		:InviwoDockWidget(tr("Help"), mainwindow)
		,mainwindow_(mainwindow)
	{
		setObjectName("HelpWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		QWidget* centralWidget = new QWidget();
		QVBoxLayout* vLayout = new QVBoxLayout(centralWidget);
		vLayout->setSpacing(7);
		vLayout->setContentsMargins(0, 0, 0, 0);

		//auto app = mainwindow_->getInviwoApplication();

		//const std::string helpfile = app->getPath(PathType::Settings, "/inviwo.qhc", true);

		//helpEngine_ = new QHelpEngineCore(QString::fromStdString(helpfile), this);


		centralWidget->setLayout(vLayout);
		setWidget(centralWidget);
	}
}
