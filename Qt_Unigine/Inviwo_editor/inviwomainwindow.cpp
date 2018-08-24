/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: inviwomainwindow
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-22 10:47:39
* --------------------------------------------------------------------------------
* DateTime : 2018/08/22
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#include "inviwomainwindow.h"
#include "inviwoapplicationqt.h"
#include "settingswidget.h"
#include "helpwidget.h"
#include "processorlistwidget.h"
#include "propertylistwidget.h"
#include <QDesktopWidget>
namespace inviwo {

	InviwoMainWindow::InviwoMainWindow(InviwoApplicationQt* app)
		:QMainWindow()
		, app_(app)
	{
		app_->setMainWindow(this);
		this->setAttribute(Qt::WA_AlwaysShowToolTips, true);


		settingsWidget_ = new settingswidget(this);
		addDockWidget(Qt::LeftDockWidgetArea, settingsWidget_);
		settingsWidget_->hide();

		helpWidget_ = new HelpWidget(this);
		addDockWidget(Qt::RightDockWidgetArea, helpWidget_);
		helpWidget_->hide();

		processorTreeWidget_ = new ProcessorTreeWidget(this, helpWidget_);
		addDockWidget(Qt::LeftDockWidgetArea, processorTreeWidget_);


		propertyListWidget_ = new PropertyListWidget(this);
		addDockWidget(Qt::RightDockWidgetArea, propertyListWidget_);
		propertyListWidget_->hide();

		const QDesktopWidget dw;
		auto screen = dw.screenGeometry(this);
		const float maxRatio = 0.8f;

		//		QApplication::instance()->installEventFilter();

		QSize size(1920, 1080);

		size.setWidth(std::min(size.width(), static_cast<int>(screen.width() * maxRatio)));
		size.setHeight(std::min(size.width(), static_cast<int>(screen.height() * maxRatio)));

		// Center Window
		QPoint pos{ screen.width() / 2 - size.width() / 2, screen.height() / 2 - size.height() / 2 };

		this->resize(size);
		this->move(pos);

		addActions();
//		this->show();
	}


	InviwoMainWindow::~InviwoMainWindow()
	{
	}

	void InviwoMainWindow::addActions()
	{
		auto menu = menuBar();

		auto fileMenuItem = menu->addMenu(tr("&File"));
		auto editMenuItem = menu->addMenu(tr("&Edit"));
		auto viewMenuItem = menu->addMenu(tr("&View"));
		auto evalMenuItem = menu->addMenu(tr("&Evaluation"));
		auto helpMenuItem = menu->addMenu(tr("&Help"));

		auto workspaceToolBar = addToolBar("File");
		workspaceToolBar->setObjectName("fileToolBar");
		auto viewModeToolBar = addToolBar("View");
		viewModeToolBar->setObjectName("viewModeToolBar");
		auto evalToolBar = addToolBar("Evaluation");
		evalToolBar->setObjectName("evalToolBar");

		{
			auto newAction = new QAction(QIcon(":/Inviwo/Resources/icons/new.png"), tr("&New Workspace"), this);
			actions_["New"] = newAction;
			newAction->setShortcut(QKeySequence::New);
			newAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(newAction);
			//connect(newAction, &QAction::triggered, this, &InviwoMainWindow::newWorkspace);
			fileMenuItem->addAction(newAction);
			workspaceToolBar->addAction(newAction);
		}

		{
			auto openAction = new QAction(QIcon(":/Inviwo/Resources/icons/open.png"), tr("&Open Workspace"), this);
			openAction->setShortcut(QKeySequence::Open);
			openAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(openAction);
			actions_["Open"] = openAction;
			//connect(openAction, &QAction::triggered, this,
			//	static_cast<void (InviwoMainWindow::*)()>(&InviwoMainWindow::openWorkspace));
			fileMenuItem->addAction(openAction);
			workspaceToolBar->addAction(openAction);
		}

		{
			auto saveAction = new QAction(QIcon(":/Inviwo/Resources/icons/save.png"), tr("&Save Workspace"), this);
			saveAction->setShortcut(QKeySequence::Save);
			saveAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(saveAction);
			actions_["Save"] = saveAction;
			/*connect(saveAction, &QAction::triggered, this,
			static_cast<void (InviwoMainWindow::*)()>(&InviwoMainWindow::saveWorkspace));*/
			fileMenuItem->addAction(saveAction);
			workspaceToolBar->addAction(saveAction);
		}

		{
			auto saveAsAction =
				new QAction(QIcon(":/Inviwo/Resources/icons/saveas.png"), tr("&Save Workspace As"), this);
			saveAsAction->setShortcut(QKeySequence::SaveAs);
			saveAsAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(saveAsAction);
			actions_["Save As"] = saveAsAction;
			//connect(saveAsAction, &QAction::triggered, this, &InviwoMainWindow::saveWorkspaceAs);
			fileMenuItem->addAction(saveAsAction);
			workspaceToolBar->addAction(saveAsAction);
		}

		{
			auto workspaceActionSaveAsCopy =
				new QAction(QIcon(":/Inviwo/Resources/icons/saveas.png"), tr("&Save Workspace As Copy"), this);
			/*connect(workspaceActionSaveAsCopy, &QAction::triggered, this,
			&InviwoMainWindow::saveWorkspaceAsCopy);*/
			fileMenuItem->addAction(workspaceActionSaveAsCopy);
		}

		//{
		//	connect(fileMenuItem->addAction("Save Network Image"), &QAction::triggered,
		//		[&](bool /*state*/) {
		//		InviwoFileDialog saveFileDialog(this, "Save Network Image ...", "image");
		//		saveFileDialog.setFileMode(FileMode::AnyFile);
		//		saveFileDialog.setAcceptMode(AcceptMode::Save);
		//		saveFileDialog.setConfirmOverwrite(true);

		//		saveFileDialog.addSidebarPath(PathType::Workspaces);
		//		saveFileDialog.addSidebarPath(workspaceFileDir_);

		//		saveFileDialog.addExtension("png", "PNG");
		//		saveFileDialog.addExtension("jpg", "JPEG");
		//		saveFileDialog.addExtension("bmp", "BMP");
		//		saveFileDialog.addExtension("pdf", "PDF");

		//		if (saveFileDialog.exec()) {
		//			QString path = saveFileDialog.selectedFiles().at(0);
		//			networkEditor_->saveNetworkImage(path.toStdString());
		//			LogInfo("Saved image of network as " << path.toStdString());
		//		}

		//	});
		//}

		{
			fileMenuItem->addSeparator();
			auto recentWorkspaceMenu = fileMenuItem->addMenu(tr("&Recent Workspaces"));
			// create placeholders for recent workspaces
			/*workspaceActionRecent_.resize(maxNumRecentFiles_);
			for (auto& action : workspaceActionRecent_) {
			action = new QAction(this);
			action->setVisible(false);
			recentWorkspaceMenu->addAction(action);
			QObject::connect(action, &QAction::triggered, this,
			&InviwoMainWindow::openRecentWorkspace);
			}*/
			// action for clearing the recent file menu
			/*clearRecentWorkspaces_ = recentWorkspaceMenu->addAction("Clear Recent Workspace List");
			clearRecentWorkspaces_->setEnabled(false);
			QObject::connect(clearRecentWorkspaces_, &QAction::triggered, this,
			&InviwoMainWindow::clearRecentWorkspaceMenu);*/
		}

		{
			// create list of all example workspaces
			exampleMenu_ = fileMenuItem->addMenu(tr("&Example Workspaces"));
			//fillExampleWorkspaceMenu();
		}

		{
			// TODO: need a DEVELOPER flag here!
			// create list of all test workspaces, inviwo-dev and other external modules, i.e.
			// "research"
			testMenu_ = fileMenuItem->addMenu(tr("&Test Workspaces"));
			//fillTestWorkspaceMenu();
		}

		{
			fileMenuItem->addSeparator();
			auto exitAction = new QAction(QIcon(":/Inviwo/Resources/icons/button_cancel.png"), tr("&Exit"), this);
			exitAction->setShortcut(QKeySequence::Close);
			connect(exitAction, &QAction::triggered, this, &InviwoMainWindow::close);
			fileMenuItem->addAction(exitAction);
		}

		//Edit
		{
			/*auto undoAction = undoManager_.getUndoAction();
			actions_["Undo"] = undoAction;
			editMenuItem->addAction(undoAction);*/
		}
		{
			/*auto redoAction = undoManager_.getRedoAction();
			actions_["Redo"] = redoAction;
			editMenuItem->addAction(redoAction);*/
		}

		editMenuItem->addSeparator();

		{
			auto cutAction = new QAction(tr("Cu&t"), this);
			actions_["Cut"] = cutAction;
			cutAction->setShortcut(QKeySequence::Cut);
			editMenuItem->addAction(cutAction);
			cutAction->setEnabled(false);
		}

		{
			auto copyAction = new QAction(tr("&Copy"), this);
			actions_["Copy"] = copyAction;
			copyAction->setShortcut(QKeySequence::Copy);
			editMenuItem->addAction(copyAction);
			// add copy action to console widget
			//			auto widget = consoleWidget_->view();
			//			auto actions = widget->actions();
			//			if (actions.isEmpty()) {
			//	widget->addAction(copyAction);
			//}
			//else {
			//	// insert copy action at the beginning
			//	widget->insertAction(actions.front(), copyAction);
			//}
			copyAction->setEnabled(false);
		}

		{
			auto pasteAction = new QAction(tr("&Paste"), this);
			actions_["Paste"] = pasteAction;
			pasteAction->setShortcut(QKeySequence::Paste);
			editMenuItem->addAction(pasteAction);
		}

		{
			auto deleteAction = new QAction(tr("&Delete"), this);
			actions_["Delete"] = deleteAction;
			deleteAction->setShortcuts(QList<QKeySequence>(
			{ QKeySequence::Delete, QKeySequence(Qt::ControlModifier + Qt::Key_Backspace) }));
			editMenuItem->addAction(deleteAction);
			deleteAction->setEnabled(false);
		}

		editMenuItem->addSeparator();

		{
			auto selectAlllAction = new QAction(tr("&Select All"), this);
			actions_["Select All"] = selectAlllAction;
			selectAlllAction->setShortcut(QKeySequence::SelectAll);
			editMenuItem->addAction(selectAlllAction);
			//connect(selectAlllAction, &QAction::triggered, [&]() { networkEditor_->selectAll(); });
		}

		editMenuItem->addSeparator();

		{
			auto findAction = new QAction(tr("&Find Processor"), this);
			actions_["Find Processor"] = findAction;
			findAction->setShortcut(QKeySequence::Find);
			editMenuItem->addAction(findAction);
			//	connect(findAction, &QAction::triggered, [&]() { processorTreeWidget_->focusSearch(); });
		}

		{
			auto addProcessorAction = new QAction(tr("&Add Processor"), this);
			actions_["Add Processor"] = addProcessorAction;
			addProcessorAction->setShortcut(Qt::ControlModifier + Qt::Key_D);
			editMenuItem->addAction(addProcessorAction);
			/*connect(addProcessorAction, &QAction::triggered,
			[&]() { processorTreeWidget_->addSelectedProcessor(); });*/
		}

		editMenuItem->addSeparator();

		{
			//auto clearLogAction = consoleWidget_->getClearAction();
			//actions_["Clear Log"] = clearLogAction;
			//editMenuItem->addAction(clearLogAction);
		}

		// View
		{
			// dock widget visibility menu entries
			viewMenuItem->addAction(settingsWidget_->toggleViewAction());

			processorTreeWidget_->toggleViewAction()->setText(tr("&Processor List"));
			viewMenuItem->addAction(processorTreeWidget_->toggleViewAction());

			propertyListWidget_->toggleViewAction()->setText(tr("&Property List"));
			viewMenuItem->addAction(propertyListWidget_->toggleViewAction());

			//consoleWidget_->toggleViewAction()->setText(tr("&Output Console"));
			//viewMenuItem->addAction(consoleWidget_->toggleViewAction());

			helpWidget_->toggleViewAction()->setText(tr("&Help"));
			viewMenuItem->addAction(helpWidget_->toggleViewAction());
		}

		// Evaluation

		// Help

		{
			//helpMenuItem->addAction(helpWidget_->toggleViewAction());

			auto aboutBoxAction = new QAction(QIcon(":/Inviwo/Resources/icons/about.png"), tr("&About"), this);
			//connect(aboutBoxAction, &QAction::triggered, this, &InviwoMainWindow::showAboutBox);
			helpMenuItem->addAction(aboutBoxAction);
		}
	}

}