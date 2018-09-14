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
#include "../inviwo-core/properties/optionproperty.h"

#include <QMainWindow>
#include <QDockWidget>
#include <QListWidget>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <unordered_map>

namespace inviwo {

	class NetworkEditorView;
	class NetworkEditor;
	class PropertyListWidget;
	class ProcessorTreeWidget;
	class ResourceManagerWidget;
	class ConsoleWidget;
	class settingswidget;
	class HelpWidget;
	class InviwoApplicationQt;
	class InviwoApplication;

	class IVW_QTEDITOR_API InviwoMainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		static const unsigned int maxNumRecentFiles_ = 10;

		InviwoMainWindow(InviwoApplicationQt* app);
		virtual ~InviwoMainWindow();

		void updateForNewModules();


		void visibilityModeChangedInSettings();


		NetworkEditor* getNetworkEditor() const;
		InviwoApplication* getInviwoApplication() const;

	public slots:
		void newWorkspace();
		void openWorkspace();

	private:
		void addActions();


		bool askToSaveWorkspaceChanges();



		void showAboutBox();

	private:

		void loadWindowState();


		void setCurrentWorkspace(QString workspaceFileName);

		void updateWindowTitle();

		InviwoApplicationQt *app_;
		std::shared_ptr<NetworkEditor> networkEditor_;
		NetworkEditorView* networkEditorView_;
		TemplateOptionProperty<UsageMode>* appUsageModeProp_;


		//dock widgets
		settingswidget* settingsWidget_;
		ProcessorTreeWidget* processorTreeWidget_;
		PropertyListWidget* propertyListWidget_;
		std::shared_ptr<ConsoleWidget> consoleWidget_;
		ResourceManagerWidget* resourceManagerWidget_;
		HelpWidget* helpWidget_;


		//menu actions
		std::unordered_map<std::string, QAction*> actions_;

		QAction* clearRecentWorkspaces_;
		QAction* visibilityModeAction_;

		QMenu* exampleMenu_ = nullptr;
		QMenu* testMenu_ = nullptr;

		// settings
		bool maximized_;

		// paths
		QString rootDir_;
		QString workspaceFileDir_;
		QString currentWorkspaceFileName_;
	};

}

#endif  // IVW_INVIWOMAINWINDOW_H