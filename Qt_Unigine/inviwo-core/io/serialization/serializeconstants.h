#ifndef IVW_SERIALIZE_CONSTANTS_H
#define IVW_SERIALIZE_CONSTANTS_H

#include "../../inviwocoredefine.h"
#include <string>

namespace inviwo {

	class IVW_CORE_API SerializeConstants {
	public:
		static const std::string XmlVersion;
		static const std::string InviwoWorkspace;
		static const int InviwoWorkspaceVersion;
		static const std::string VersionAttribute;
		static const std::string ContentAttribute;
		static const std::string KeyAttribute;

		// For reference management
		static const std::string TypeAttribute;
		static const std::string RefAttribute;
		static const std::string IDAttribute;

		static const std::string VectorAttributes[4];
	};

} //namespace

#endif
