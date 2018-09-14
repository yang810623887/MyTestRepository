#include "processornetwork.h"
#include "../util/stdextensions.h"

namespace inviwo {

	ProcessorNetwork::ProcessorNetwork()
	{
	}


	ProcessorNetwork::~ProcessorNetwork()
	{
	}

	bool ProcessorNetwork::isEmpty() const
	{
		return processors_.empty();
	}

	std::vector<Processor*> ProcessorNetwork::getProcessors() const
	{
		return util::transform(processors_,
			[](ProcessorMap::const_reference elem) { return elem.second; });
	}

}