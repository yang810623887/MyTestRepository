#include "propertywidgetqt.h"


#include <QApplication>
#include <QDesktopWidget>
#include <QStyleOption>
#include <QPainter>
#include <QToolTip>
#include <QHelpEvent>
#include <QInputDialog>
#include <QClipboard>
#include <QMenu>
#include <QLayout>
#include <QMimeData>
#include <QMessageBox>

namespace inviwo {
	const int PropertyWidgetQt::minimumWidth = 250;
	const int PropertyWidgetQt::spacing = 7;
	const int PropertyWidgetQt::margin = 0;

	void PropertyWidgetQt::setParentPropertyWidget(PropertyWidgetQt* parent, InviwoDockWidget* widget)
	{
		parent_ = parent;
		baseContainer_ = widget;
	}

	PropertyWidgetQt::PropertyWidgetQt(Property* property /*= nullptr*/)
	{

	}

	void PropertyWidgetQt::initState()
	{
		if (property_)
		{
			//setDisabled(property_->getReadOnly());
		}
	}

	inviwo::PropertyWidgetQt::~PropertyWidgetQt()
	{

	}




}