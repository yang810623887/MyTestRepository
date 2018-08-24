/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: inviwomainwindow
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-22 10:44:28
* --------------------------------------------------------------------------------
* DateTime : 2018/08/22
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_INVIWOMAINWINDOW_H
#define IVW_INVIWOMAINWINDOW_H

#include "inviwoqteditordefine.h"

#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <memory>
#include <unordered_map>

namespace inviwo {

	class InviwoApplicationQt;
	class NetworkEditorView;
	class NetworkEditor;
	class settingswidget;
	class ProcessorTreeWidget;
	class PropertyListWidget;
	class HelpWidget;
	class ConsoleWidget;

	class IVW_QTEDITOR_API InviwoMainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		InviwoMainWindow(InviwoApplicationQt* app);
		~InviwoMainWindow();

		InviwoApplicationQt* getInviwoApplication() const;

	private:
		void addActions();

	private:
		InviwoApplicationQt * app_;


		//dock widgets
		settingswidget* settingsWidget_;
		ProcessorTreeWidget* processorTreeWidget_;
		PropertyListWidget* propertyListWidget_;
		std::shared_ptr<ConsoleWidget> consoleWidget_;
		HelpWidget* helpWidget_;


		//menu actions
		std::unordered_map<std::string, QAction*> actions_;

		QAction* clearRecentWorkspaces_;
		QAction* visibilityModeAction_;

		QMenu* exampleMenu_ = nullptr;
		QMenu* testMenu_ = nullptr;
	};

}

#endif  // IVW_INVIWOMAINWINDOW_H