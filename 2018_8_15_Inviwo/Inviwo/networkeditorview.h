#pragma once

#ifndef IVW_NETWORKEDITORVIEW_H
#define IVW_NETWORKEDITORVIEW_H

#include "networkeditor.h"

#include <QGraphicsView>

namespace inviwo {

	class InviwoMainWindow;

	class NetworkEditorView : public QGraphicsView
	{
	public:
		NetworkEditorView(NetworkEditor* networkEditor, InviwoMainWindow* parent = nullptr);
		~NetworkEditorView();

	private:
		InviwoMainWindow * mainwindow_;
		NetworkEditor* networkEditor_;
	};

}
#endif