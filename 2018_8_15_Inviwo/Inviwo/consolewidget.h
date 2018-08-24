#pragma once

#ifndef IVW_CONSOLEWIDGET_H
#define IVW_CONSOLEWIDGET_H

#include "InviwoDockWidget.h"

namespace inviwo {

	class InviwoMainWindow;

	class ConsoleWidget : public InviwoDockWidget
	{
		Q_OBJECT
	public:
		ConsoleWidget(InviwoMainWindow* parent);
		~ConsoleWidget();
	};
}

#endif

