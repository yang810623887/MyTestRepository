#ifndef IVW_SERIALIZER_H
#define IVW_SERIALIZER_H

#include "serializebase.h"
#include "../../util/exception.h"
#include "../../util/stdextensions.h"
#include "../../util/stringconversion.h"
#include "serializationexception.h"

#include "../../ext/flags/flags.h"

#include <type_traits>
#include <list>

namespace inviwo {
	class Serializable;
	class IVW_CORE_API Serializer : public SerializeBase
	{
	public:
		Serializer(const std::string& fileName, bool allowReference = true);
		~Serializer();
	};

}
#endif