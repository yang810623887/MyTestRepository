#pragma once

#include <QSplashScreen>

namespace inviwo {

	class InviwoSplashScreen : public QSplashScreen
	{
		Q_OBJECT

	public:
		InviwoSplashScreen(bool enable = true);
		~InviwoSplashScreen();

		virtual void show();
		virtual void drawContents(QPainter* painter);
		virtual void showMessage(std::string message);
		virtual void finish(QWidget* waitfor);

	private:
		bool showSplashScreen_;
	};

}