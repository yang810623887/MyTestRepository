#ifndef IVW_INVIWODOCKWIDGET_H
#define IVW_INVIWODOCKWIDGET_H
#include <QDockWidget>
#include "qtwidgetsmoduledefine.h"

namespace inviwo {

	class InviwoDockWidgetTitleBar;

class IVW_MODULE_QTWIDGETS_API InviwoDockWidget : public QDockWidget
{
	Q_OBJECT
public:
	InviwoDockWidget(QString title, QWidget* parent);
	~InviwoDockWidget();
	virtual void showEvent(QShowEvent* showEvent) override;
	virtual void keyPressEvent(QKeyEvent* keyEvent) override;

	void setSticky(bool sticky);
	bool isSticky() const;

	void setContents(QWidget *widget);
	void setContents(QLayout *layout);

signals:
	void stickyFlagChanged(bool sticky);

private:
	InviwoDockWidgetTitleBar * dockWidgetTitleBar_;
};

} // namespace

#endif // IVW_INVIWODOCKWIDGET_H