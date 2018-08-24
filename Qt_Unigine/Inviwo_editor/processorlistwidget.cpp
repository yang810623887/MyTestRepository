#include "processorlistwidget.h"
#include "processorpreview.h"
#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMimeData>
#include <QHeaderView>
namespace inviwo {

	//////////////////////////////////////////////////////////////////////////
	// Class Processortree
	const int ProcessorTree::IDENTIFIER_ROLE = Qt::UserRole + 1;

	ProcessorTree::ProcessorTree(QWidget* parent)
		: QTreeWidget(parent)
	{
	}

	void ProcessorTree::mousePressEvent(QMouseEvent * e)
	{
		if (e->buttons() & Qt::LeftButton)
		{
			dragStartPosition_ = e->pos();
		}
		QTreeWidget::mousePressEvent(e);
	}

	void ProcessorTree::mouseMoveEvent(QMouseEvent * e)
	{
		if (e->buttons() & Qt::LeftButton)
		{
			if ((e->pos() - dragStartPosition_).manhattanLength() < QApplication::startDragDistance())
			{
				return;
			}

			QTreeWidgetItem * selectedProcessor = itemAt(dragStartPosition_);

			if (selectedProcessor && selectedProcessor->parent())
			{
				new ProcessorDragObject(this, selectedProcessor->data(0, IDENTIFIER_ROLE).toString());
			}
		}
	}



	//////////////////////////////////////////////////////////////////////////
	//Class ProcessorDragObject
	static QString mimeType = "inviwo/ProcessorDragObject";

	ProcessorDragObject::ProcessorDragObject(QWidget * source, const QString className)
		: QDrag(source)
	{
		QByteArray byteData;
		{
			QDataStream ds(&byteData, QIODevice::WriteOnly);
			ds << className;
		}

		QMimeData* mimeData = new QMimeData;
		mimeData->setData(mimeType, byteData);
		mimeData->setData("text/plain", className.toLatin1().data());
		setMimeData(mimeData);

		auto img = QPixmap::fromImage(utilqt::generateProcessorPreview(className, 0.8));
		setPixmap(img);
		setHotSpot(QPoint(img.width() / 2, img.height() / 2));
		start(Qt::MoveAction);
	}

	bool ProcessorDragObject::canDecode(const QMimeData* mimeData)
	{
		if (mimeData->hasFormat(mimeType))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ProcessorDragObject::decode(const QMimeData * mimeData, QString & className)
	{
		QByteArray byteData = mimeData->data(mimeType);
		if (byteData.isEmpty())
		{
			return false;
		}

		QDataStream ds(&byteData, QIODevice::ReadOnly);
		ds >> className;
		return true;
	}


	//////////////////////////////////////////////////////////////////////////
	//Class ProcessorTreeWidget

	ProcessorTreeWidget::ProcessorTreeWidget(QWidget* parent, HelpWidget* helpWidget)
		: InviwoDockWidget(tr("Processors"), parent)
		,helpWidget_(helpWidget)
	{
		setObjectName("ProcessorTreeWidget");
		setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		QWidget* centralWidget = new QWidget();
		QVBoxLayout* vLayout = new QVBoxLayout(centralWidget);
		vLayout->setSpacing(7);
		vLayout->setContentsMargins(7, 7, 7, 7);

		lineEdit_ = new QLineEdit(centralWidget);
		lineEdit_->setPlaceholderText("Filter processor list...");
		lineEdit_->setClearButtonEnabled(true);

		connect(lineEdit_, SIGNAL(textChanged(const QString&)), this, SLOT(addProcessorsToTree));
		vLayout->addWidget(lineEdit_);

		QHBoxLayout *listViewLayout = new QHBoxLayout();
		listViewLayout->addWidget(new QLabel("Group by", centralWidget));
		listView_ = new QComboBox(centralWidget);
		listView_->addItem("Alphabet");
		listView_->addItem("Category");
		listView_->addItem("Code State");
		listView_->addItem("Module");
		listView_->setCurrentIndex(1);
		connect(listView_, SIGNAL(currentIndexChanged(int)), this, SLOT(addProcessorsToTree()));
		listView_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
		listViewLayout->addWidget(listView_);
		vLayout->addLayout(listViewLayout);

		iconStable_ = QIcon(":/icons/processor_stable.png");
		iconExperimental_ = QIcon(":/icons/processor_experimental.png");
		iconBroken_ = QIcon(":/icons/processor_broken.png");
		
		processorTree_ = new ProcessorTree(this);
		processorTree_->setHeaderHidden(true);
		processorTree_->setColumnCount(2);
		processorTree_->setIndentation(10);
		processorTree_->setAnimated(true);
		processorTree_->header()->setStretchLastSection(false);
		processorTree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
		processorTree_->header()->setSectionResizeMode(1, QHeaderView::Fixed);
		processorTree_->header()->setDefaultSectionSize(40);

		connect(processorTree_, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this,
			SLOT(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));

		addProcessorsToTree();
		vLayout->addWidget(processorTree_);
		centralWidget->setLayout(vLayout);
		setWidget(centralWidget);
	}

	void ProcessorTreeWidget::focusSearch()
	{
		raise();
		lineEdit_->setFocus();
		lineEdit_->selectAll();
	}

	//slot function
	void ProcessorTreeWidget::addProcessorsToTree()
	{
		processorTree_->clear();

//		InviwoApplication *inviwoApp = InviwoApplication::getPtr();
	}

}
