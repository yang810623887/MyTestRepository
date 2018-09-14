#include "collapsiblegroupboxwidgetqt.h"
//#include "../edi"

#include <QLineEdit>
#include <QToolButton>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QMenu>
#include <QAction>

namespace inviwo {

	inviwo::CollapsibleGroupBoxWidgetQt::CollapsibleGroupBoxWidgetQt(Property* property, bool isCheckable /*= false*/)
	{

	}

	CollapsibleGroupBoxWidgetQt::CollapsibleGroupBoxWidgetQt(std::string displayName /*= ""*/, bool isCheckable /*= false*/)
		:PropertyWidgetQt()
		,displayName_(displayName)
		,collapsed_(false)
		,checked_(false)
		//,propertyOw
	{
		setObjectName("CompositeWidget");

		generateWidget();
	}

	void CollapsibleGroupBoxWidgetQt::generateWidget()
	{
		propertyWidgetGroupLayout_ = new QGridLayout();
		propertyWidgetGroupLayout_->setAlignment(Qt::AlignTop);
		propertyWidgetGroupLayout_->setContentsMargins(PropertyWidgetQt::spacing, PropertyWidgetQt::spacing, 0, PropertyWidgetQt::spacing);
		propertyWidgetGroupLayout_->setHorizontalSpacing(0);
		propertyWidgetGroupLayout_->setVerticalSpacing(PropertyWidgetQt::spacing);

		propertyWidgetGroup_ = new QWidget(this);
		propertyWidgetGroup_->setObjectName("CompositeContents");
		propertyWidgetGroup_->setLayout(propertyWidgetGroupLayout_);

		defaultLabel_ = new QLabel("No properties available");

		propertyWidgetGroupLayout_->addWidget(defaultLabel_, 0, 0);
		propertyWidgetGroupLayout_->addItem(
			new QSpacerItem(PropertyWidgetQt::spacing, 1, QSizePolicy::Fixed), 0, 1);
		propertyWidgetGroupLayout_->setColumnStretch(0, 1);
		propertyWidgetGroupLayout_->setColumnStretch(1, 0);

		btnCollapse_ = new QToolButton(this);
		btnCollapse_->setObjectName("collapseButton");
		btnCollapse_->setIcon(QIcon(":/stylesheets/images/arrow_lighter_down.png"));

		connect(btnCollapse_, &QToolButton::clicked, this,
			&CollapsibleGroupBoxWidgetQt::toggleCollapsed);

		/*if (property_) {
			label_ = new EditableLabelQt(this, property_, false);
		}
		else {
			label_ = new EditableLabelQt(this, displayName_, false);
		}*/

		/*label_->setObjectName("compositeLabel");
		QSizePolicy labelPol = label_->sizePolicy();
		labelPol.setHorizontalStretch(10);
		label_->setSizePolicy(labelPol);*/
	}

	void CollapsibleGroupBoxWidgetQt::addProperty(Property* prop)
	{
		properties_.push_back(prop);
	}

	bool CollapsibleGroupBoxWidgetQt::isCollapsed() const
	{
		return collapsed_;
	}

	void CollapsibleGroupBoxWidgetQt::toggleCollapsed()
	{
		setCollapsed(!isCollapsed());
	}

	void CollapsibleGroupBoxWidgetQt::updatePropertyWidgetSemantics(PropertyWidgetQt* widget)
	{
		Property* prop = widget->getProperty();
	}

	void CollapsibleGroupBoxWidgetQt::setCollapsed(bool collapse)
	{
		setUpdatesEnabled(false);
		if (collapsed_ && !collapse)
		{
			propertyWidgetGroup_->show();
			btnCollapse_->setIcon(QIcon(":/stylesheets/images/arrow_darker_down.png"));
		} 
		else if(!collapsed_ && collapse)
		{
			propertyWidgetGroup_->show();
			btnCollapse_->setIcon(QIcon(":/stylesheets/images/arrow_darker_right.png"));
		}
		collapsed_ = collapse;
		setUpdatesEnabled(true);
	}



}