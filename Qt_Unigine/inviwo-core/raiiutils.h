/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: raiiutils
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-23 14:46:38
* --------------------------------------------------------------------------------
* DateTime : 2018/08/23
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_RAIIUTILS_H
#define IVW_RAIIUTILS_H

#include "inviwocoredefine.h"

namespace inviwo {

	namespace util {

		class /*IVW_CORE_API*/ KeepTrueWhileInScope {

		public:
			KeepTrueWhileInScope(bool* b)
				: variable_(b)
			{
				if (variable_)
					(*variable_) = true;
			}
			~KeepTrueWhileInScope() { if (variable_) (*variable_) = false; }
		private:
			bool* variable_;
		};
	}

}

#endif