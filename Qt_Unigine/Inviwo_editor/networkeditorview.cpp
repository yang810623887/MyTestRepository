#include "networkeditorview.h"
#include "inviwomainwindow.h"

#include <QMatrix>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QApplication>
#include <QClipboard>

namespace inviwo {



	NetworkEditorView::NetworkEditorView(NetworkEditor* networkEditor, InviwoMainWindow* parent /*= nullptr*/)
		: QGraphicsView(parent)
		, mainwindow_(parent)
		, networkEditor_(networkEditor)
	{

		QGraphicsView::setScene(networkEditor_);

		setRenderHint(QPainter::Antialiasing, true);
		setMouseTracking(true);
		setDragMode(QGraphicsView::RubberBandDrag);
		setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		setCacheMode(QGraphicsView::CacheBackground);

		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

		/*loadHandle_ = mainwindow_->getInviwoApplication()->getWorkspaceManager()->onLoad(
			[this](Deserializer&) { fitNetwork(); });*/
		fitNetwork();
	}

	NetworkEditorView::~NetworkEditorView()
	{

	}

	void NetworkEditorView::hideNetwork(bool hide)
	{
		if (hide)
		{
				if (scene())
				{
					scrollPos_.x = horizontalScrollBar()->value();
					scrollPos_.y = verticalScrollBar()->value();
					QGraphicsView::setScene(nullptr);
				}
		} 
		else
		{
			if (scene() != networkEditor_)
			{
				QGraphicsView::setScene(networkEditor_);
				horizontalScrollBar()->setValue(scrollPos_.x);
				verticalScrollBar()->setValue(scrollPos_.y);
			}
		}
	}

	void NetworkEditorView::fitNetwork()
	{
		QRectF br = networkEditor_->itemsBoundingRect().adjusted(-50, -50, 50, 50);
		QSizeF viewsize = size();
		QSizeF brsize = br.size();

		if (brsize.width() < viewsize.width()) {
			br.setLeft(br.left() - 0.5*(viewsize.width() - brsize.width()));
			br.setRight(br.right() + 0.5*(viewsize.width() - brsize.width()));
		}
		if (brsize.height() < viewsize.height()) {
			br.setTop(br.top() - 0.5*(viewsize.height() - brsize.height()));
			br.setBottom(br.bottom() + 0.5*(viewsize.height() - brsize.height()));
		}

		setSceneRect(br);
		fitInView(br, Qt::KeepAspectRatio);
	}

}