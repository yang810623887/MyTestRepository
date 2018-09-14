/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: networkeditorview
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-29 14:17:21
* --------------------------------------------------------------------------------
* DateTime : 2018/08/29
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_NETWORKEDITORVIEW_H
#define IVW_NETWORKEDITORVIEW_H

#include "inviwoqteditordefine.h"
#include "networkeditor.h"

#include <QGraphicsView>

namespace inviwo {
	class InviwoMainWindow;

	class IVW_QTEDITOR_API NetworkEditorView : public QGraphicsView
	{
	public:
		NetworkEditorView(NetworkEditor* networkEditor, InviwoMainWindow* parent = nullptr);
		~NetworkEditorView();

		void hideNetwork(bool);

	private:
		void fitNetwork();

		InviwoMainWindow* mainwindow_;
		NetworkEditor* networkEditor_;
		ivec2 scrollPos_;
	};

}
#endif