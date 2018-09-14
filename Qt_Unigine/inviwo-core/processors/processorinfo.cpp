#include "processorinfo.h"

namespace inviwo {

	ProcessorInfo::ProcessorInfo(std::string aClassIdentifier, std::string aDisplayName, std::string aCategory, CodeState aCodeState, Tags someTags)
		: classIdentifier(aClassIdentifier)
		, displayName(aDisplayName)
		, category(aCategory)
		, codeState(aCodeState)
		, tags(someTags)
	{

	}

}