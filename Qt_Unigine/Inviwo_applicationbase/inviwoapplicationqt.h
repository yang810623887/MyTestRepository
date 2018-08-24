/*********************************************************************************
*
* NameSpace: Inviwo_applicationbase
* ClassName: inviwoapplicationqt
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 13:55:36
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#pragma once

#include "qtapplicationbasemoduledefine.h"

#include <QMainWindow>
#include <QApplication>
namespace  inviwo {
	class IVW_QTAPPLICATIONBASE_API InviwoApplicationQt : public QApplication
	{
		Q_OBJECT
	public:
		InviwoApplicationQt(int& argc, char** argv);

		void setMainWindow(QMainWindow* mainWindow);

	private:
		QMainWindow * mainWindow_;
	};
}
