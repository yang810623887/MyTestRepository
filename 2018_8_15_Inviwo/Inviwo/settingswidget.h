#ifndef IVW_SETTINGSWIDGET_H
#define IVW_SETTINGSWIDGET_H

#include "InviwoDockWidget.h"
#include "InviwoMainWindow.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QString>

namespace inviwo {

class settingswidget : public InviwoDockWidget
{
	Q_OBJECT
public:
	settingswidget(InviwoMainWindow* parent);

	settingswidget(QString title, InviwoMainWindow* parent);
	~settingswidget();

	virtual void updateSettingsWidget();
	virtual void saveSettings();

public slots:
//	void updatePropertyWidgetSemantics(PropertyWidgetQt*);
	virtual void closeEvent(QCloseEvent *event) override;

protected:
	InviwoMainWindow * mainwindow_;
	QVBoxLayout* layout_ = nullptr;
	QWidget* mainWidget_ = nullptr;
	QScrollArea* scrollArea_ = nullptr;
};

} // namespace
#endif // IVW_SETTINGSWIDGET_H