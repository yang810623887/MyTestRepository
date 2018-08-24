#include "networkeditorview.h"
#include "InviwoMainWindow.h"


namespace inviwo {
	NetworkEditorView::NetworkEditorView(NetworkEditor* networkEditor, InviwoMainWindow* parent)
		:QGraphicsView(parent)
		, networkEditor_(networkEditor)
	{
		QGraphicsView::setScene(networkEditor_);

		setRenderHint(QPainter::Antialiasing, true);
		setMouseTracking(true);
		setDragMode(QGraphicsView::RubberBandDrag);
		setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		setCacheMode(QGraphicsView::CacheBackground);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


	}


	NetworkEditorView::~NetworkEditorView()
	{
	}
}