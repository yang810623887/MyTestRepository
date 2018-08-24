#pragma once
#ifndef IVW_HELPWIDGET_H
#define IVW_HELPWIDGET_H

#include "InviwoDockWidget.h"
#include "inviwomainwindow.h"
#include "inviwoqteditordefine.h"

namespace inviwo {

	class IVW_QTEDITOR_API HelpWidget : public InviwoDockWidget {

	public:
		HelpWidget(InviwoMainWindow* mainwindow);
		virtual ~HelpWidget() = default;
		HelpWidget(const HelpWidget&) = delete;
		HelpWidget& operator=(const HelpWidget&) = delete;

	//	void showDocForClassName(std::string className);
	//	void registerQCHFiles();

	//protected:
	//	virtual void resizeEvent(QResizeEvent* event) override;
	private:
		InviwoMainWindow * mainwindow_;
//		QHelpEngineCore* helpEngine_;
//		HelpBrowser* helpBrowser_;
		std::string current_;
//		std::unique_ptr<QCHFileObserver> fileObserver_;
	};

}
#endif  // IVW_HELPWIDGET_H