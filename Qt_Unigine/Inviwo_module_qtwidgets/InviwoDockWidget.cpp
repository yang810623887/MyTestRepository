#include "InviwoDockWidget.h"
#include "InviwoDockWidgetTitleBar.h"
#include <QKeyEvent>


namespace inviwo {
	InviwoDockWidget::InviwoDockWidget(QString title, QWidget *parent) : QDockWidget(title, parent)
	{
		setObjectName(title);
#ifdef __APPLE__
		setStyleSheet("QDockWidget::title {padding-left: 45px; }");
#endif

		dockWidgetTitleBar_ = new InviwoDockWidgetTitleBar(this);
		setTitleBarWidget(dockWidgetTitleBar_);


		QObject::connect(this, &QDockWidget::topLevelChanged, dockWidgetTitleBar_,
			&InviwoDockWidgetTitleBar::floating);
		QObject::connect(this, &QDockWidget::windowTitleChanged,
			[&](const QString &str) { dockWidgetTitleBar_->setLabel(str); });
		QObject::connect(dockWidgetTitleBar_, &InviwoDockWidgetTitleBar::stickyFlagChanged, this,
			&InviwoDockWidget::stickyFlagChanged);
		QObject::connect(this, &QDockWidget::allowedAreasChanged, dockWidgetTitleBar_,
			&InviwoDockWidgetTitleBar::allowedAreasChanged);
	}

	InviwoDockWidget::~InviwoDockWidget() = default;

	void InviwoDockWidget::showEvent(QShowEvent *showEvent) {
		raise();
		QDockWidget::showEvent(showEvent);
	}

	void InviwoDockWidget::keyPressEvent(QKeyEvent *keyEvent) {
		if (keyEvent->key() == Qt::Key_Escape && isFloating()) {
			hide();
		}
		else {
			keyEvent->ignore();
		}
		QDockWidget::keyPressEvent(keyEvent);
	}

	void InviwoDockWidget::setSticky(bool sticky) { dockWidgetTitleBar_->setSticky(sticky); }
	bool InviwoDockWidget::isSticky() const { return dockWidgetTitleBar_->isSticky(); }

	void InviwoDockWidget::setContents(QWidget *widget) {
		QWidget *oldWidget = this->widget();
		if (oldWidget) {
			this->setWidget(nullptr);
			delete oldWidget;
		}

		this->setWidget(widget);
	}

	void InviwoDockWidget::setContents(QLayout *layout) {
		QWidget *oldWidget = this->widget();
		if (oldWidget) {
			this->setWidget(nullptr);
			delete oldWidget;
		}

		QWidget *centralWidget = new QWidget();
		centralWidget->setLayout(layout);
		this->setWidget(centralWidget);
	}
}