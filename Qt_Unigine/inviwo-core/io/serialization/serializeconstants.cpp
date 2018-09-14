#include "serializeconstants.h"

namespace inviwo {
	const std::string SerializeConstants::XmlVersion = "1.0";
	const std::string SerializeConstants::InviwoWorkspace = "InviwoWorkspace";
	const int SerializeConstants::InviwoWorkspaceVersion = 2;
	const std::string SerializeConstants::VersionAttribute = "version";
	const std::string SerializeConstants::ContentAttribute = "content";
	const std::string SerializeConstants::KeyAttribute = "key";

	const std::string SerializeConstants::TypeAttribute = "type";
	const std::string SerializeConstants::RefAttribute = "reference";
	const std::string SerializeConstants::IDAttribute = "id";

	const std::string SerializeConstants::VectorAttributes[] = { "x", "y", "z", "w" };

}