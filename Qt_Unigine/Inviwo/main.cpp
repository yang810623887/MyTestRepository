//
//
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMainWindow>
#include <QDesktopWidget>
#include "InviwoSplashScreen.h"
#include "inviwoapplicationqt.h"
//#include "../inviwo-core/inviwoapplication.h"
#include "../Inviwo_applicationbase/inviwoapplicationqt.h"
#include "inviwomainwindow.h"
#include "AppEditorLogic.h"
#include "AppSystemLogic.h"
#include "AppWorldLogic.h"
#include <../build/_generated/moduleregistration.h>

#include "AppQt.h"
#include <UnigineEngine.h>

// Common
#include "GLAppQt.h"
#ifdef _WIN32
#include "D3D11AppQt.h"
#endif

enum
{
	RENDER_OPENGL,
	RENDER_D3D11,
};

int get_render_api()
{
#ifdef _WIN32
	const int DEFAULT = RENDER_D3D11;
#else
	const int DEFAULT = RENDER_OPENGL;
#endif

	QStringList arguments = qApp->arguments();
	int index = arguments.indexOf("-video_app");
	if (index == -1)
		return DEFAULT;

	if (index + 1 >= arguments.size())
	{
		arguments.removeAt(index);
		return DEFAULT;
	}

	if (arguments[index + 1] == "opengl")
		return RENDER_OPENGL;
#ifdef _WIN32
	if (arguments[index + 1] == "direct3d11")
		return RENDER_D3D11;
#endif
	return DEFAULT;
}

int main(int argc, char *argv[])
{
//	inviwo::LogCentral::init();

	inviwo::InviwoApplicationQt inviwoApp("Inviwo v 0.9.9", argc, argv);
	inviwoApp.setWindowIcon(QIcon(":/icons/inviwo_light.png"));
	inviwoApp.setAttribute(Qt::AA_NativeWindows);

	QFile styleSheetFile(":/stylesheets/inviwo.qss");
	styleSheetFile.open(QFile::ReadOnly);
	QString styleSheet = QString::fromUtf8(styleSheetFile.readAll());
	inviwoApp.setStyleSheet(styleSheet);
	styleSheetFile.close();

	inviwo::InviwoMainWindow mainWin( &inviwoApp );

	// initialize and show splash screen
	//inviwo::InviwoSplashScreen splashScreen(true);
	inviwoApp.setProgressCallback([&](std::string s)
	{
		
	});
	//splashScreen.show();
	//splashScreen.showMessage("Loading application...");


	inviwoApp.registerModules(&inviwo::registerAllModules);
	inviwoApp.processEvents();

	mainWin.updateForNewModules();


	//unigine

//	AppQt  *widget = NULL;
//	if (get_render_api() == RENDER_OPENGL)
//		widget = new GLAppQt(&mainWin);
//	else
//	{
//#ifdef _WIN32
//		widget = new D3D11AppQt(&mainWin);
//#endif
//	}
//
//
//	Unigine::EnginePtr engine(UNIGINE_VERSION, widget, argc, argv);
//
//
//	// enter main loop
//	AppSystemLogic system_logic;
//	AppWorldLogic world_logic;
//
//	engine->addSystemLogic(&system_logic);
//	engine->addWorldLogic(&world_logic);
//	//engine->addEditorLogic(&editor_logic);
//
//	mainWin.setWindowTitle("main_qt");
//	mainWin.setCentralWidget(widget);
//	mainWin.move((QApplication::desktop()->screen()->width() - mainWin.width()) / 2, (QApplication::desktop()->screen()->height() - mainWin.height()) / 2);
	mainWin.show();
	return inviwoApp.exec();
}
