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
#include "../inviwo-core/inviwoapplication.h"
#include "../inviwo-core/network/processornetwork.h"
#include "../inviwo-core/util/filesystem.h"
#include "../inviwo-core/util/settings/systemsettings.h"


#include "inviwoapplicationqt.h"
#include "settingswidget.h"
#include "helpwidget.h"
#include "processorlistwidget.h"
#include "propertylistwidget.h"
#include "consolewidget.h"
#include "networkeditorview.h"
#include "resourcemanagerwidget.h"


#include <QSettings>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>

namespace inviwo {

	InviwoMainWindow::InviwoMainWindow(InviwoApplicationQt* app)
		:QMainWindow()
		, app_(app)
		,networkEditor_(nullptr)		
	{
		app_->setMainWindow(this);
		// make sure, tooltips are always shown (this includes port inspectors as well)
		this->setAttribute(Qt::WA_AlwaysShowToolTips, true);

		networkEditor_ = std::make_shared<NetworkEditor>(this);
		// initialize console widget first to receive log messages
		consoleWidget_ = std::make_shared<ConsoleWidget>(this);
		//********************
		currentWorkspaceFileName_ = "";

		const QDesktopWidget dw;
		auto screen = dw.screenGeometry(this);
		const float maxRatio = 0.8f;

		//QApplication::instance()->installEventFilter();

		QSize size(1920, 1080);

		size.setWidth(std::min(size.width(), static_cast<int>(screen.width() * maxRatio)));
		size.setHeight(std::min(size.width(), static_cast<int>(screen.height() * maxRatio)));

		// Center Window
		QPoint pos{ screen.width() / 2 - size.width() / 2, screen.height() / 2 - size.height() / 2 };

		this->resize(size);
		this->move(pos);


		networkEditorView_ = new NetworkEditorView(networkEditor_.get(), this);
//		NetworkEditorObserver::addObservation(networkEditor_.get());
		setCentralWidget(networkEditorView_);

		resourceManagerWidget_ = new ResourceManagerWidget(this);
		addDockWidget(Qt::LeftDockWidgetArea, resourceManagerWidget_);
		resourceManagerWidget_->hide();

		settingsWidget_ = new settingswidget(this);
		addDockWidget(Qt::LeftDockWidgetArea, settingsWidget_);
		//settingsWidget_->hide();

		helpWidget_ = new HelpWidget(this);
		addDockWidget(Qt::RightDockWidgetArea, helpWidget_);
		//helpWidget_->hide();

		processorTreeWidget_ = new ProcessorTreeWidget(this, helpWidget_);
		addDockWidget(Qt::LeftDockWidgetArea, processorTreeWidget_);


		propertyListWidget_ = new PropertyListWidget(this);
		addDockWidget(Qt::RightDockWidgetArea, propertyListWidget_);
		//propertyListWidget_->hide();

		addDockWidget(Qt::BottomDockWidgetArea, consoleWidget_.get());
		// load settings and restore window state
		loadWindowState();
		

		rootDir_ = QString::fromStdString(filesystem::getPath(PathType::Data));

		addActions();
//		this->show();
	}


	InviwoMainWindow::~InviwoMainWindow()
	{
	}

	void InviwoMainWindow::updateForNewModules()
	{
		settingsWidget_->updateSettingsWidget();
		processorTreeWidget_->addProcessorsToTree();
		//helpWidget_->registerQCHFiles();
	}

	void InviwoMainWindow::visibilityModeChangedInSettings()
	{
		if (appUsageModeProp_)
		{
			auto network = getInviwoApplication()->getProcessorNetwork();
			switch (appUsageModeProp_->getSelectedValue())
			{
			case UsageMode::Development:
			{
				for (auto& p : network->getProcessors())
				{
// 					auto md =
// 						p->getMetaData<ProcessorMetaData>(ProcessorMetaData::CLASS_IDENTIFIER);
					//if (md->isSelected()) {
					//	propertyListWidget_->addProcessorProperties(p);
					//}
					//else {
					//	propertyListWidget_->removeProcessorProperties(p);
					//}
				}
			}
			networkEditorView_->hideNetwork(false);
			break;
			case UsageMode::Application:
			{

			}
			break;
			}
		}
	}

	NetworkEditor* InviwoMainWindow::getNetworkEditor() const
	{
		return networkEditor_.get();
	}

	InviwoApplication* InviwoMainWindow::getInviwoApplication() const
	{
		return app_;
	}

	void InviwoMainWindow::newWorkspace()
	{
		if (currentWorkspaceFileName_ != "")
		{
 			if (!askToSaveWorkspaceChanges())
 			{
				return;
 			}
		}
		app_->getWorkspaceManager()->clear();

		setCurrentWorkspace(rootDir_ + "/workspaces/untitled.inv");
		getNetworkEditor()->setModified(false);
	}

	void InviwoMainWindow::openWorkspace()
	{
		if (askToSaveWorkspaceChanges())
		{
			
		}
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
			auto newAction = new QAction(QIcon(":/icons/new.png"), tr("&New Workspace"), this);
			actions_["New"] = newAction;
			newAction->setShortcut(QKeySequence::New);
			newAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(newAction);
			connect(newAction, &QAction::triggered, this, &InviwoMainWindow::newWorkspace);
			fileMenuItem->addAction(newAction);
			workspaceToolBar->addAction(newAction);
		}

		{
			auto openAction = new QAction(QIcon(":/icons/open.png"), tr("&Open Workspace"), this);
			openAction->setShortcut(QKeySequence::Open);
			openAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
			this->addAction(openAction);
			actions_["Open"] = openAction;
			connect(openAction, &QAction::triggered, this,
			static_cast<void (InviwoMainWindow::*)()>(&InviwoMainWindow::openWorkspace));
			fileMenuItem->addAction(openAction);
			workspaceToolBar->addAction(openAction);
		}

		{
			auto saveAction = new QAction(QIcon(":/icons/save.png"), tr("&Save Workspace"), this);
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
				new QAction(QIcon(":/icons/saveas.png"), tr("&Save Workspace As"), this);
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
				new QAction(QIcon(":/icons/saveas.png"), tr("&Save Workspace As Copy"), this);
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
			auto exitAction = new QAction(QIcon(":/icons/button_cancel.png"), tr("&Exit"), this);
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

		{
			QIcon visibilityModeIcon;
			visibilityModeIcon.addFile(":/icons/view-developer.png", QSize(), QIcon::Normal,
				QIcon::Off);
			visibilityModeIcon.addFile(":/icons/view-application.png", QSize(), QIcon::Normal,
				QIcon::On);
			visibilityModeAction_ = new QAction(visibilityModeIcon, tr("&Application Mode"), this);
			visibilityModeAction_->setCheckable(true);
			visibilityModeAction_->setChecked(false);

			viewMenuItem->addAction(visibilityModeAction_);
			viewModeToolBar->addAction(visibilityModeAction_);

			//appUsageModeProp_ = &InviwoApplication::getPtr()
			//	->getSettingsByType<SystemSettings>()
			//	->applicationUsageMode_;

			//appUsageModeProp_->onChange

			connect(visibilityModeAction_, &QAction::triggered, [&](bool appView)
			{
				auto selectedIdx = appUsageModeProp_->getSelectedValue();
				if (appView)
				{
					//if (selectedIdx != UsageMode::Application)
					//{
					//	appUsageModeProp_->setSelec
					//}
				} 
				else
				{
				}
			});

			visibilityModeChangedInSettings();

		}
		// Evaluation

		// Help

		{
			helpMenuItem->addAction(helpWidget_->toggleViewAction());

			auto aboutBoxAction = new QAction(QIcon(":/icons/about.png"), tr("&About"), this);
			connect(aboutBoxAction, &QAction::triggered, this, &InviwoMainWindow::showAboutBox);
			helpMenuItem->addAction(aboutBoxAction);
		}
	}

	bool InviwoMainWindow::askToSaveWorkspaceChanges()
	{
		bool continueOperation = true;

		if (getNetworkEditor()->isModified() && !app_->getProcessorNetwork()->isEmpty())
		{
			QMessageBox msgBox(this);
			msgBox.setText("Workspace Modified");
			msgBox.setInformativeText("Do you want to save your changes?");
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Yes);

			int answer = msgBox.exec();

			switch (answer) {
			case QMessageBox::Yes:
				//saveWorkspace();
				break;

			case QMessageBox::No:
				break;

			case QMessageBox::Cancel:
				continueOperation = false;
				break;
			}
		}

		return continueOperation;
	}

	void InviwoMainWindow::showAboutBox()
	{
		//auto caps = InviwoApplication::getPtr()->getModuleByType

		//const int buildYear = (syscap ? syscap->getBuildTimeYear() : 0);
		std::stringstream aboutText;
		aboutText << "<html><head>\n"
			<< "<style>\n"
			<< "table { margin-top:0px;margin-bottom:0px; }\n"
			<< "table > tr > td { "
			<< "padding-left:0px; padding-right:0px;padding-top:0px; \n"
			<< "padding-bottom:0px;"
			<< "}\n"
			<< "</style>\n"
			<< "<head/>\n"
			<< "<body>\n"

			<< "<b>Inviwo v" << IVW_VERSION << "</b><br>\n"
			<< "Interactive Visualization Workshop<br>\n"
			<< "&copy; 2012-" << 2018 << " The Inviwo Foundation<br>\n"
			<< "<a href='http://www.inviwo.org/' style='color: #AAAAAA;'>"
			<< "http://www.inviwo.org/</a>\n"
			<< "<p>Inviwo is a rapid prototyping environment for interactive "
			<< "visualizations.<br>It is licensed under the Simplified BSD license.</p>\n"

			<< "<p><b>Core Team:</b><br>\n"
			<< "Peter Steneteg, Erik Sund&eacute;n, Daniel J&ouml;nsson, Martin Falk, "
			<< "Rickard Englund, Sathish Kottravel, Timo Ropinski</p>\n"

			<< "<p><b>Former Developers:</b><br>\n"
			<< "Alexander Johansson, Andreas Valter, Johan Nor&eacute;n, Emanuel Winblad, "
			<< "Hans-Christian Helltegen, Viktor Axelsson</p>\n";

		auto str = aboutText.str();

		auto about =
			new QMessageBox(QMessageBox::NoIcon, QString::fromStdString("Inviwo v" + IVW_VERSION),
				QString::fromStdString(aboutText.str()), QMessageBox::Ok, this);
		auto icon = windowIcon();
		about->setIconPixmap(icon.pixmap(256));
		about->setTextInteractionFlags(Qt::TextBrowserInteraction);
		about->exec();
	}

	void InviwoMainWindow::loadWindowState()
	{
		// load settings and restore window state
		QSettings settings("Inviwo", "Inviwo");
		settings.beginGroup("mainwindow");
		restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
		restoreState(settings.value("state", saveState()).toByteArray());
		maximized_ = settings.value("maximized", false).toBool();

		// restore sticky flags for main dock widgets
		settings.beginGroup("dialogs");
		settingsWidget_->setSticky(settings.value("settingswidgetSticky", true).toBool());
		processorTreeWidget_->setSticky(settings.value("processorwidgetSticky", true).toBool());
		propertyListWidget_->setSticky(settings.value("propertywidgetSticky", true).toBool());
		consoleWidget_->setSticky(settings.value("consolewidgetSticky", true).toBool());
		resourceManagerWidget_->setSticky(settings.value("resourcemanagerwidgetSticky", true).toBool());
		helpWidget_->setSticky(settings.value("helpwidgetSticky", true).toBool());

	}

	void InviwoMainWindow::setCurrentWorkspace(QString workspaceFileName)
	{
		workspaceFileDir_ = QFileInfo(workspaceFileName).absolutePath();
		currentWorkspaceFileName_ = workspaceFileName;
		updateWindowTitle();
	}

	void InviwoMainWindow::updateWindowTitle()
	{
		QString windowTitle = QString("Inviwo - Interactive Visualization Workshop - ");
		windowTitle.append(currentWorkspaceFileName_);
		if (getNetworkEditor()->isModified())
		{
			windowTitle.append("*");
		}
		if (visibilityModeAction_->isChecked())
		{
			windowTitle.append(" (Application mode)");
		} 
		else
		{
			windowTitle.append(" (Developer mode)");
		}
		setWindowTitle(windowTitle);
	}

}