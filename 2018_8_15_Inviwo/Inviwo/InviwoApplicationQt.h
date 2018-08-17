#pragma once
#include <QMainWindow>
#include <QApplication>
namespace inviwo {
	class InviwoApplicationQt : public QApplication
	{
		Q_OBJECT
	public:
		InviwoApplicationQt(int& argc, char** argv);

		void setMainWindow(QMainWindow* mainWindow);

	private:
		QMainWindow * mainWindow_;
	};
}