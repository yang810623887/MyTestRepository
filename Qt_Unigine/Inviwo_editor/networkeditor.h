/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: networkeditor
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-29 14:08:45
* --------------------------------------------------------------------------------
* DateTime : 2018/08/29
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_NETWORKEDITOR_H
#define IVW_NETWORKEDITOR_H

#include "inviwoqteditordefine.h"
#include "networkeditorobserver.h"
#include "../inviwo-core/util/observer.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

namespace inviwo {

	class ProcessorNetwork;
	class InviwoMainWindow;

	class IVW_QTEDITOR_API NetworkEditor : public QGraphicsScene
	{
		Q_OBJECT
	public:
		NetworkEditor(InviwoMainWindow* mainwindow);
		virtual ~NetworkEditor() = default;

		bool isModified() const;
		void setModified(const bool modified = true);


	private:

		ProcessorNetwork* network_;

		bool modified_;
	};
}
#endif