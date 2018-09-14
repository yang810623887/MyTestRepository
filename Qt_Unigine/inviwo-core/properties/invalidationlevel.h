#ifndef IVW_INVALIDATIONLEVEL_H
#define IVW_INVALIDATIONLEVEL_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"

namespace inviwo {

	/**
	* invalidation level must be sorted based on their complexity, whereby higher numbers (later entry
	* in the list) involve more expensive update operations
	*/
	enum class InvalidationLevel {
		Valid,            // Do nothing.
		InvalidOutput,    // Trigger a process call.
		InvalidResources  // Trigger a call to initializeResources and then process.
	};

	template <class Elem, class Traits>

	std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& ss, const InvalidationLevel& level)
	{
		switch (level) 
		{
		case InvalidationLevel::Valid:
			ss << "Valid";
			break;
		case InvalidationLevel::InvalidOutput:
			ss << "Invalid output";
			break;
		case InvalidationLevel::InvalidResources:
			ss << "Invalid resources";
			break;
		default:
			ss << "Unknown";
			break;
		}

		return ss;
	}
}

#endif