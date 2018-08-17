

#include <QtWidgets/QApplication>
#include <QFile>
#include <QMainWindow>
#include "InviwoSplashScreen.h"
#include "InviwoMainWindow.h"
#include "InviwoApplicationQt.h"

int main(int argc, char *argv[])
{

	inviwo::InviwoApplicationQt inviwoApp(argc, argv);
	inviwoApp.setWindowIcon(QIcon(":/Inviwo/Resources/icons/inviwo_light.ico"));
	inviwoApp.setAttribute(Qt::AA_NativeWindows);

	QFile styleSheetFile(":/Inviwo/Resources/stylesheets/inviwo.qss");
	styleSheetFile.open(QFile::ReadOnly);
	QString styleSheet = QString::fromUtf8(styleSheetFile.readAll());
	inviwoApp.setStyleSheet(styleSheet);
	styleSheetFile.close();

	inviwo::InviwoMainWindow mainWin( &inviwoApp );

	


	inviwo::InviwoSplashScreen splashScreen(true);

	//splashScreen.show();
	//splashScreen.showMessage("Loading application...");

	return inviwoApp.exec();
}
