#ifndef IVW_PROCESSORNETWORK_H
#define IVW_PROCESSORNETWORK_H

#include "../inviwo.h"
#include "../inviwocoredefine.h"
#include "../processors/processor.h"

#include <unordered_map>

namespace inviwo {

	class InviwoApplication;

	class IVW_CORE_API ProcessorNetwork
	{
	public:
		using ProcessorMap = std::unordered_map<std::string, Processor*>;
		ProcessorNetwork();
		~ProcessorNetwork();

		bool isEmpty() const;

		std::vector<Processor*> getProcessors() const;
	private:

		ProcessorMap processors_;
	};

}
#endif