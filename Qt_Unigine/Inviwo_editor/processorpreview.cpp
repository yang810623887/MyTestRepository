/*********************************************************************************
*
* NameSpace: Inviwo_editor
* ClassName: processorpreview
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 10:58:09
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#include "processorpreview.h"
#include "inviwoapplicationqt.h"

namespace inviwo {

	class InviwoApplication;

	namespace utilqt {




		IVW_QTEDITOR_API QImage generateProcessorPreview(const QString& classIdentifier, double opacity /*= 1.0*/)
		{
			std::string cid = classIdentifier.toLocal8Bit().constData();

			try
			{
				//auto processor = InviwoApplication::getPtr()
				return QImage();
			}
			catch (const std::exception&)
			{
				return QImage();
			}
		}

	}
}