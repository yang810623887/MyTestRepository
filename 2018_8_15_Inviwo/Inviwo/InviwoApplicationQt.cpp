#include "InviwoApplicationQt.h"
namespace inviwo {

	InviwoApplicationQt::InviwoApplicationQt(int &argc, char** argv)
		: QApplication(argc, argv)
	{

	}

	void InviwoApplicationQt::setMainWindow(QMainWindow * mainWindow)
	{
		mainWindow_ = mainWindow;
		mainWindow_->setObjectName("InviwoMainWindow");
	}
}