/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: serializable
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 14:57:50
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_SERIALIZABLE_H
#define IVW_SERIALIZABLE_H
#include "../../inviwocoredefine.h"

namespace inviwo {

	class Serializer;
	class Deserializer;
	class SerializeBase;

	class IVW_CORE_API Serializable {
	public:
		virtual ~Serializable() = default;
		virtual void serialize(Serializer& s) const = 0;
		virtual void deserialize(Deserializer& d) = 0;
	};

#endif
