/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: processorpreview
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 10:54:39
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORPREVIEW_H
#define IVW_PROCESSORPREVIEW_H

#include "inviwoqteditordefine.h"

#include <QImage>
#include <QString>

namespace inviwo {

	class InviwoApplication;

	namespace utilqt {

		//************************************
		// Method     : generateProcessorPreview
		// FullName   : inviwo::utilqt::generateProcessorPreview
		// Parameter  : const QString & classIdentifier
		// Parameter  : double opacity
		// Description: Generate an image Preview of the Processor
		//************************************
		IVW_QTEDITOR_API QImage generateProcessorPreview(const QString& classIdentifier, double opacity = 1.0);


	}
}

#endif
