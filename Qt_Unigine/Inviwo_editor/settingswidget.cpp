#include "settingswidget.h"
#include "../Inviwo_module_qtwidgets/properties/propertywidgetqt.h"
#include "../inviwo-core/inviwoapplication.h"
#include "../Inviwo_module_qtwidgets/properties/collapsiblegroupboxwidgetqt.h"
#include "../inviwo-core/util/settings/settings.h"


#include <QLayout>
#include <QFrame>

namespace inviwo {

	settingswidget::settingswidget(QString title, InviwoMainWindow* mainwindow)
		: InviwoDockWidget(title, mainwindow)
		, mainwindow_(mainwindow)
	{
		setObjectName("SettingsWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		scrollArea_ = new QScrollArea();
		scrollArea_->setWidgetResizable(true);
		scrollArea_->setMinimumWidth(300);
		scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		scrollArea_->setFrameShape(QFrame::NoFrame);
		scrollArea_->setContentsMargins(0, 0, 0, 0);

		mainWidget_ = new QWidget();
		layout_ = new QVBoxLayout(mainWidget_);
		layout_->setAlignment(Qt::AlignTop);
		layout_->setContentsMargins(0, PropertyWidgetQt::spacing, 0, PropertyWidgetQt::spacing);
		layout_->setContentsMargins(0, 1, 0, 1);
		layout_->setSpacing(7);
		scrollArea_->setWidget(mainWidget_);

		setWidget(scrollArea_);
	}
	settingswidget::settingswidget(InviwoMainWindow* mainwindow)
		: settingswidget(tr("Settings"), mainwindow) {}

	settingswidget::~settingswidget() = default;

	void inviwo::settingswidget::updateSettingsWidget()
	{
		auto settings = mainwindow_->getInviwoApplication()->getModuleSettings();

		for (auto &setting : settings)
		{
			CollapsibleGroupBoxWidgetQt* settingsGroup =
				new CollapsibleGroupBoxWidgetQt(setting->getIdentifier());
			settingsGroup->setParentPropertyWidget(nullptr, this);
			layout_->addWidget(settingsGroup);
			settingsGroup->initState();

			std::vector<Property*> props = setting->getProperties();

			for (auto& prop : props)
			{
				settingsGroup->addProperty(prop);
				for (auto p : prop->getWidgets())
				{
					connect(static_cast<PropertyWidgetQt*>(p),
						SIGNAL(updateSemantics(PropertyWidgetQt*)), this,
						SLOT(updatePropertyWidgetSemantics(PropertyWidgetQt*)));
				}
			}
			if (!settingsGroup->isCollapsed())
			{
				settingsGroup->toggleCollapsed();
			}
		}
		layout_->addStretch();
	}

	void inviwo::settingswidget::saveSettings()
	{
	}

	void settingswidget::closeEvent(QCloseEvent *event) {
		saveSettings();
		InviwoDockWidget::closeEvent(event);
	}
}
