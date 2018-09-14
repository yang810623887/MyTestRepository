#include "helpwidget.h"
#include "processorpreview.h"
#include "../inviwo-core/inviwoapplication.h"
#include "../inviwo-core/util/filesystem.h"
#include "../inviwo-core/util/fileobserver.h"
#include "../inviwo-core/inviwomodule.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QHelpEngineCore>
#include <QUrlQuery>
#include <QByteArray>
#include <QBuffer>

namespace inviwo {


	class HelpBrowser : public QTextBrowser
	{
	public:
		HelpBrowser(HelpWidget* parent, QHelpEngineCore* helpEngine);
		virtual ~HelpBrowser() = default;

	protected:
		QVariant loadResource(int type, const QUrl& name);

	private:
		QHelpEngineCore* helpEngine_;
	};

	class QCHFileObserver : public FileObserver {
	public:
		QCHFileObserver(InviwoApplication* app, QHelpEngineCore* engine) : app_(app), engine_(engine)
		{
			//app_->re
		}
		virtual ~QCHFileObserver()
		{

		}
	private:
		InviwoApplication* app_;
		QHelpEngineCore* engine_;
	};

	HelpBrowser::HelpBrowser(HelpWidget* parent, QHelpEngineCore* helpEngine)
		: QTextBrowser(parent)
		, helpEngine_ (helpEngine)
	{
		setReadOnly(true);
		setUndoRedoEnabled(false);
		setContextMenuPolicy(Qt::NoContextMenu);
		setAcceptRichText(false);
	}

	QVariant HelpBrowser::loadResource(int type, const QUrl& name)
	{
		QUrl url(name);
		if (name.isRelative())
		{
			url = source().resolved(url);
		}

		QUrlQuery query(url);
		if (query.hasQueryItem("classIdentifier"))
		{
			QString cid = query.queryItemValue("classIdentifier");

			/*auto img = utilqt::generatePreview(cid);
			if (img.isNull()) return QVariant();*/
			QByteArray imgData;
			QBuffer buffer(&imgData);
			buffer.open(QIODevice::WriteOnly);
			//img.save(&buffer, "PNG");
			return imgData;
		}

		QByteArray fileData = helpEngine_->fileData(url);
		switch (type)
		{
		case QTextDocument::HtmlResource:
			return fileData;
		case QTextDocument::StyleSheetResource:
			return fileData;
		case QTextDocument::ImageResource:
		{
			/*auto image =
				QImage::fromData(fileData, QFileInfo(url.path()).suffix().toLatin1().data());
			QImage resized{
				image.scaled(std::max(200, width() - 60), image.height(), Qt::KeepAspectRatio) };*/

			QByteArray smalldata;
			/*QBuffer buffer(&smalldata);
			resized.save(&buffer, QFileInfo(url.path()).suffix().toLatin1().data());*/
			return smalldata;
		}
		}

	}

	HelpWidget::HelpWidget(InviwoMainWindow * mainwindow)
		: InviwoDockWidget(tr("Help"), mainwindow)
		, mainwindow_(mainwindow)
		, helpEngine_(nullptr)
		, helpBrowser_(nullptr)
	{
		setObjectName("HelpWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

		QWidget* centralWidget = new QWidget();
		QVBoxLayout* vLayout = new QVBoxLayout(centralWidget);
		vLayout->setSpacing(7);
		vLayout->setContentsMargins(0, 0, 0, 0);

		auto app = mainwindow->getInviwoApplication();

		//const std::string helpfile = app->getPath(PathType::Settings, "/inviwo.qhc", true);

		//helpEngine_ = new QHelpEngineCore(QString::fromStdString(helpfile), this);

		//for (const auto& ns : helpEngine_->registeredDocumentations())
		//{
		//	helpEngine_->unregisterDocumentation(ns);
		//}

		helpBrowser_ = new HelpBrowser(this, helpEngine_);
		helpBrowser_->setHtml(QString("Hello world"));
		vLayout->addWidget(helpBrowser_);
		centralWidget->setLayout(vLayout);
		setWidget(centralWidget);

		connect(helpEngine_, &QHelpEngineCore::setupFinished, this,
			[&]() {
			if (!helpEngine_)
			{
				return;
			}
			if (current_.empty())
			{
				helpBrowser_->setText("Select a processor in the processor list to see help");
			} 
			else
			{
				showDocForClassName(current_);
			}
		});

		//if (!helpEngine_->setupData())
		//{
		//	//const std::string error{ helpEngine_->error().toUtf8().constData() };
		//	//delete helpEngine_;
		//	//throw Exception("Failed to setup the help engine:" + error);
		//}

		//fileObserver_ = util::make_unique<QCHFileObserver>(app, helpEngine_);
	}

	void HelpWidget::showDocForClassName(std::string classIdentifier)
	{
		if (!helpEngine_)
		{
			return;
		}

		current_ = classIdentifier;

		const QString path("qthelp:///doc/docpage-%1.html");
		helpBrowser_->setText(
			QString::fromStdString("No documentation available for: " + current_));
	}

	void HelpWidget::registerQCHFiles()
	{
		auto app = mainwindow_->getInviwoApplication();
		for (const auto& module : app->getModules())
		{
			const auto moduleQchFile =
				module->getPath(ModulePath::Docs) + "/" + module->getIdentifier() + ".qch";
			if (filesystem::fileExists(moduleQchFile))
			{
				//fileObserver_->addFile(moduleQchFile);
			}
		}
	}

}
