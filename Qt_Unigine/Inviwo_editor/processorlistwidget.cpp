#include "processorlistwidget.h"
#include "processorpreview.h"
#include "../inviwo-core/inviwomodule.h"
#include "../inviwo-core/inviwoapplication.h"
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

		InviwoApplication *inviwoApp = InviwoApplication::getPtr();

		if (listView_->currentIndex() == 2)
		{
			addToplevelItemTo("Stable Processors", "");
			addToplevelItemTo("Experimental Processors", "");
			addToplevelItemTo("Broken Processors", "");
		}

		for (auto &elem : inviwoApp->getModules())
		{
			std::vector<ProcessorFactoryObject*> curProcessorList = elem->getProcessors();

			QList<QTreeWidgetItem*> items;
			for (auto &processor : curProcessorList)
			{
				if (lineEdit_->text().isEmpty() || processorFits(processor, lineEdit_->text()))
				{
					std::string categoryName;
					std::string categoryDesc;

					switch (listView_->currentIndex())
					{
					case 0:
						categoryName = processor->getDisplayName().substr(0, 1);
						categoryDesc = "";
						break;
					case 1:  // By Category
						categoryName = processor->getCategory();
						categoryDesc = "";
						break;
					//case 2:  // By Code State
					//	categoryName = Processor::getCodeStateString(processor->getCodeState());
					//	categoryDesc = "";
					//	break;
					case 3:  // By Module
						categoryName = elem->getIdentifier();
						categoryDesc = elem->getDescription();
						break;
					default:
						categoryName = "Unkonwn";
						categoryDesc = "";
					}
					QString category = QString::fromStdString(categoryName);
					items = processorTree_->findItems(category, Qt::MatchFixedString, 0);

					if (items.empty()) items.push_back(addToplevelItemTo(category, categoryDesc));
					addProcessorItemTo(items[0], processor, elem->getIdentifier());
				}
			}
		}

		// Apply sorting
		switch (listView_->currentIndex())
		{
		case 2:
		{
			int i = 0;
			while (i < processorTree_->topLevelItemCount())
			{
				QTreeWidgetItem* item = processorTree_->topLevelItem(i);
				if (item->childCount() == 0)
				{
					delete processorTree_->takeTopLevelItem(i);
				}
				else
				{
					item->sortChildren(0, Qt::AscendingOrder);
					i++;
				}
			}
			break;
		}
		default:
			processorTree_->sortItems(0, Qt::AscendingOrder);
			break;
		}
		
		processorTree_->expandAll();
		processorTree_->resizeColumnToContents(1);
	}

	bool ProcessorTreeWidget::processorFits(ProcessorFactoryObject* processor, const QString& filter)
	{
		return(
			QString::fromStdString(processor->getDisplayName()).contains(filter, Qt::CaseInsensitive) ||
			QString::fromStdString(processor->getClassIdentifier()).contains(filter, Qt::CaseInsensitive) ||
			QString::fromStdString(processor->getTags().getString()).contains(filter, Qt::CaseInsensitive)
			);
	}

	const QIcon* ProcessorTreeWidget::getCodeStateIcon(CodeState state) const
	{
		switch (state)
		{
		case CodeState::Stable:
			return &iconStable_;

		case CodeState::Broken:
			return &iconBroken_;

		case CodeState::Experimental:
		default:
			return &iconExperimental_;
		}
	}

	void ProcessorTreeWidget::currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem*)
	{
		if (!current)
		{
			return;
		}
		std::string classname = current->data(0, ProcessorTree::IDENTIFIER_ROLE).toString().toUtf8().constData();

		if (!classname.empty())
		{
//			helpWidget_->showDocForClassName(classname);
		}
	}

	QTreeWidgetItem* ProcessorTreeWidget::addToplevelItemTo(QString title, const std::string& desc)
	{
		QTreeWidgetItem* newItem = new QTreeWidgetItem(QStringList(title));


		if (!desc.empty())
		{
			//newItem->setToolTip(0, utilqt::toLo)
		}
		processorTree_->addTopLevelItem(newItem);
		processorTree_->setFirstItemColumnSpanned(newItem, true);

		return newItem;
	}

	QTreeWidgetItem* ProcessorTreeWidget::addProcessorItemTo(QTreeWidgetItem* item, ProcessorFactoryObject* processor, std::string moduleId)
	{
		QTreeWidgetItem* newItem = new QTreeWidgetItem();
		newItem->setIcon(0, *getCodeStateIcon(processor->getCodeState()));
		newItem->setText(0, QString::fromStdString(processor->getDisplayName()));
		newItem->setTextAlignment(1, Qt::AlignRight);
		newItem->setData(0, ProcessorTree::IDENTIFIER_ROLE,
			QString::fromStdString(processor->getClassIdentifier()));


		auto platformTags = util::getPlatformTags(processor->getTags());
		const bool hasTags = !platformTags.empty();

		//if (hasTags)
		//{
		//	newItem->setText(1, utilqt::toQString(platformTags.getString() + " "));

		//	QFont font = newItem->font(1);
		//	font.setWeight(QFont::Bold);
		//	newItem->setFont(1, font);

		//}

		{

		}

		item->addChild(newItem);

		if (!hasTags)
		{
			processorTree_->setFirstItemColumnSpanned(newItem, true);
		}
		return newItem;
	}

}
