#ifndef IVW_PROPERTYVISIBILITYMODE_H
#define IVW_PROPERTYVISIBILITYMODE_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"

namespace inviwo {

	enum class UsageMode {
		Application = 0, // Always show property
		Development = 1, // Default, Only show in developer mode
	};

	template <class Elem, class Traits>
	std::basic_ostream<Elem, Traits>& operator<< (std::basic_ostream<Elem, Traits>& ss, const UsageMode& mode)
	{
		switch (mode)
		{
		case UsageMode::Application:
			ss << "Application";
			break;
		case UsageMode::Development:
			ss << "Development";
			break;
		}

		return ss;
	}

}

#endif
