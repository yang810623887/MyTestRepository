#pragma once

#ifndef IVW_CONSOLEWIDGET_H
#define IVW_CONSOLEWIDGET_H

#include "InviwoDockWidget.h"
#include "inviwoqteditordefine.h"

namespace inviwo {

	class InviwoMainWindow;

	class IVW_QTEDITOR_API ConsoleWidget : public InviwoDockWidget
	{
		Q_OBJECT
	public:
		ConsoleWidget(InviwoMainWindow* parent);
		~ConsoleWidget();
	};
}

#endif

