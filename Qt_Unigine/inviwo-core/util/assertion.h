#ifndef IVW_ASSERTION_H
#define IVW_ASSERTION_H

#include "../inviwocoredefine.h"
#include <ostream>
#include <string>

namespace inviwo {
	IVW_CORE_API void ivwAssertion(const char* fileName, const char* functionName, long lineNumber,
		std::string message);

	namespace util {

		IVW_CORE_API void debugBreak();

	}  // namespace
}

#if defined(IVW_DEBUG)
#define ivwAssert(condition, message)                                                  \
    {                                                                                  \
                                                                                       \
        if (!(bool(condition))){                                                       \
            std::ostringstream stream__;                                               \
            stream__ << message;                                                       \
            inviwo::ivwAssertion(__FILE__, __FUNCTION__, __LINE__, (stream__.str()));  \
        }                                                                              \
    }
#else
#define ivwAssert(condition, message)
#endif

#endif