/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: inviwoapplication
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 13:59:04
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_INVIWOAPPLICATION_H
#define IVW_INVIWOAPPLICATION_H

#include "singleton.h"
#include "inviwocoredefine.h"
namespace inviwo {
	class IVW_CORE_API InviwoApplication// : public Singleton<InviwoApplication>
	{
	public:
		InviwoApplication();
		~InviwoApplication();
	};
}
#endif