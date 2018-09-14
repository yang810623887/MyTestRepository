/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processorstate
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 16:30:12
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORSTATE_H
#define IVW_PROCESSORSTATE_H

#include "../inviwocoredefine.h"
#include <ostream>

namespace inviwo {

	enum class CodeState {
		Broken,
		Experimental,
		Stable
	};

	template <class Elem, class Traits>

	std::basic_ostream<Elem, Traits>& operator << (std::basic_ostream<Elem, Traits>& ss, CodeState cs)
	{
		switch (cs)
		{
		case inviwo::CodeState::Broken:
			ss << "Broken";
			break;
		case inviwo::CodeState::Experimental:
			ss << "Experimental";
			break;
		case inviwo::CodeState::Stable:
			ss << "Stable";
			break;
		default:
			ss << "Not specified";
			break;
		}
		return ss;
	}

}

#endif
