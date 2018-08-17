#pragma once
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <InviwoApplicationQt.h>


#include <unordered_map>

namespace inviwo{

	//class ConsoleWidget;
	class settingswidget;
	class ProcessorTreeWidget;
	class PropertyListWidget;
	class HelpWidget;


	class InviwoMainWindow : public QMainWindow
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
		HelpWidget* helpWidget_;
		//std::shared_ptr<ConsoleWidget> consoleWidget_;


		//menu actions
		std::unordered_map<std::string, QAction*> actions_;

		QAction* clearRecentWorkspaces_;
		QAction* visibilityModeAction_;

		QMenu* exampleMenu_ = nullptr;
		QMenu* testMenu_ = nullptr;
	};

}