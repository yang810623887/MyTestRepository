#include "processorlistwidget.h"
#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMimeData>
#include <QHeaderView>
namespace inviwo {

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
				//new ProcessorDragObject(this, selectedProcessor->data(0, IDENTIFIER_ROLE).toString());
			}
		}
	}

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

		//auto img = QPixmap::fromImage(utilqt::generateProcessorPreview(className, 0.8));
		/*setPixmap(img);
		setHotSpot(QPoint(img.width() / 2, img.height() / 2));
		start(Qt::MoveAction);*/
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

		centralWidget->setLayout(vLayout);
		setWidget(centralWidget);
	}

}
