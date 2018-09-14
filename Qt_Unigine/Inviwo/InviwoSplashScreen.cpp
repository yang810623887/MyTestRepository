#include "InviwoSplashScreen.h"
#include <QApplication>
#include <QPainter>
#include <QSplashScreen>
#include <QTextStream>
#include <QDesktopWidget>
namespace inviwo {

	InviwoSplashScreen::InviwoSplashScreen(bool enable)
		: QSplashScreen(QPixmap(":/images/splashscreen.png")), showSplashScreen_(enable) {}

	InviwoSplashScreen::~InviwoSplashScreen()
	{
	}
	void InviwoSplashScreen::show() {
		if (showSplashScreen_) QSplashScreen::show();
	}

	void InviwoSplashScreen::drawContents(QPainter* painter) {
		QString versionLabel;
		QTextStream labelStream(&versionLabel);
		labelStream << "Version " << QString::fromStdString("0.0.9");
		painter->setPen(Qt::black);
		painter->drawText(12, 266, versionLabel);
		auto font = painter->font();
		font.setPointSizeF(font.pointSizeF()*0.8f);
		painter->setFont(font);
		painter->drawText(12, 286, message());
	}
	void InviwoSplashScreen::showMessage(std::string message) {
		if (showSplashScreen_) QSplashScreen::showMessage(QString::fromStdString(message));
	}

	void InviwoSplashScreen::finish(QWidget* waitFor) {
		if (showSplashScreen_) QSplashScreen::finish(waitFor);
	}
}