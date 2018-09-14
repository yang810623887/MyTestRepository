#include "inviwoapplicationqt.h"
namespace inviwo {

	InviwoApplicationQt::InviwoApplicationQt(std::string displayName, int &argc, char** argv)
		: QApplication(argc, argv)
		, InviwoApplication(argc, argv, displayName)
		, mainWindow_(nullptr)
	{

	}

	void InviwoApplicationQt::setMainWindow(QMainWindow* mainWindow)
	{
		mainWindow_ = mainWindow;
		mainWindow_->setObjectName("InviwoMainWindow");
	}

}
