/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: pathtype
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 17:36:25
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PATHTYPE_H
#define IVW_PATHTYPE_H

#include "../inviwocoredefine.h"

namespace inviwo {

	enum class PathType {
		Data,               // /data
		Volumes,            // /data/volumes
		Workspaces,         // /data/workspaces
		Scripts,            // /data/scripts
		PortInspectors,     // /data/workspaces/portinspectors
		Images,             // /data/images
		Databases,          // /data/databases
		Resources,          // /resources
		TransferFunctions,  // /data/transferfunctions
		Settings,           // path to the current users settings
		Help,               // /data/help
		Tests               // /tests
	};

}

#endif