#ifndef IVW_INVIWODOCKWIDGETTITLEBAR_H
#define IVW_INVIWODOCKWIDGETTITLEBAR_H

#include <QWidget>

#include "qtwidgetsmoduledefine.h"
#include "util/raiiutils.h"

class QPaintEvent;
class QDockWidget;
class QToolButton;
class QLabel;

namespace inviwo {

	

	class IVW_MODULE_QTWIDGETS_API InviwoDockWidgetTitleBar : public QWidget
	{
		Q_OBJECT
	public:
		InviwoDockWidgetTitleBar(QWidget *parent = nullptr);
		virtual ~InviwoDockWidgetTitleBar();

		virtual void paintEvent(QPaintEvent *) override;

		void setLabel(const QString &str);
		void setSticky(bool toggle);
		bool isSticky() const;
		void allowedAreasChanged(Qt::DockWidgetAreas areas);
		void floating(bool floating);
	signals:
		void stickyFlagChanged(bool sticky);
	protected slots:
		virtual void showEvent(QShowEvent *event) override;

	private:
		void stickyBtnToggled(bool toggle);

		QDockWidget *parent_;

		QLabel* label_;
		QToolButton *stickyBtn_;
		QToolButton *floatBtn_;
		Qt::DockWidgetAreas allowedDockAreas_;

		bool internalStickyFlagUpdate_;
	};


} // namespace

#endif // IVW_INVIWODOCKWIDGETTITLEBAR_H