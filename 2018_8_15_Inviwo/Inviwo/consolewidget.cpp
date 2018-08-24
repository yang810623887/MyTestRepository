#include "consolewidget.h"
#include "InviwoMainWindow.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QString>

namespace inviwo {

	ConsoleWidget::ConsoleWidget(InviwoMainWindow* parent)
		: InviwoDockWidget(tr("Console"), parent)
	{
		setObjectName("ConsoleWidget");
		setAllowedAreas(Qt::BottomDockWidgetArea);

		QScrollArea *scrollArea_ = new QScrollArea();
		scrollArea_ = new QScrollArea();
		scrollArea_->setWidgetResizable(true);
		scrollArea_->setMinimumWidth(300);
		scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		scrollArea_->setFrameShape(QFrame::NoFrame);
		scrollArea_->setContentsMargins(0, 0, 0, 0);

		QWidget *mainWidget_ = new QWidget();
		QVBoxLayout *layout_ = new QVBoxLayout(mainWidget_);
		layout_->setAlignment(Qt::AlignTop);
		//layout_->setContentsMargins(0, PropertyWidgetQt::spacing, 0, PropertyWidgetQt::spacing);
		layout_->setContentsMargins(0, 1, 0, 1);
		layout_->setSpacing(7);
		scrollArea_->setWidget(mainWidget_);

		setWidget(scrollArea_);
	}


	ConsoleWidget::~ConsoleWidget()
	{
	}
}


