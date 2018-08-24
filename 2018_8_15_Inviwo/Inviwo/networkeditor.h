#pragma once
#ifndef IVW_NETWORKEDITOR_H
#define IVW_NETWORKEDITOR_H

#include <QGraphicsScene>
#include <QGraphicsItem>

namespace inviwo {

	class InviwoMainWindow;


	class NetworkEditor : public QGraphicsScene
	{
	public:
		NetworkEditor(InviwoMainWindow* mainwindow);
		~NetworkEditor() = default;
	};

}

#endif