#include "propertylistwidget.h"
#include "properties\propertywidgetqt.h"


#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QSettings>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

namespace inviwo {
	PropertyListFrame::PropertyListFrame(QWidget * parent)
		: QWidget(parent)
	{
		QSizePolicy sp(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
		sp.setVerticalStretch(0);
		sp.setHorizontalStretch(1);
		QWidget::setSizePolicy(sp);
	}

	QSize PropertyListFrame::sizeHint() const
	{
		QSize size = layout()->minimumSize();
		size.setHeight(parentWidget()->width());
		return size;
	}

	QSize PropertyListFrame::minimumSizeHint() const
	{
		QSize size = layout()->minimumSize();
		size.setWidth(parentWidget()->width());
		return size;
	}

	void PropertyListFrame::paintEvent(QPaintEvent*)
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	PropertyListWidget::PropertyListWidget(QWidget* parent)
		: InviwoDockWidget(tr("Properties"), parent)
	{
		setObjectName("ProcessorListWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		QSizePolicy sp(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
		sp.setVerticalStretch(1);
		sp.setHorizontalStretch(1);
		setSizePolicy(sp);

		scrollArea_ = new QScrollArea(this);
		scrollArea_->setWidgetResizable(true);
		scrollArea_->setMinimumWidth(320);
		scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
#ifdef __APPLE__
		// Scrollbars are overlayed in different way on mac...
		scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
#else
		scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif
		scrollArea_->setFrameShape(QFrame::NoFrame);
		//scrollArea_->setContentsMargins(0, PropertyWidgetQt::spacing, 0, PropertyWidgetQt::spacing);
	}

}
