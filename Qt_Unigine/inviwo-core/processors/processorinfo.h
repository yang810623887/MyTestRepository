/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processorinfo
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 16:42:00
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_PROCESSORINFO_H
#define IVW_PROCESSORINFO_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "processorstate.h"
#include "processortags.h"

namespace inviwo {

	class IVW_CORE_API ProcessorInfo
	{
	public:
		ProcessorInfo( std::string aClassIdentifier, std::string aDisplayName, std::string aCategory, CodeState aCodeState, Tags someTags);

		const std::string classIdentifier;
		const std::string displayName;
		const std::string category;
		const CodeState codeState;
		const Tags tags;
	};

}
#endif