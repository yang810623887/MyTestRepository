#ifndef IVW_PROCESSORFACTORY_H
#define IVW_PROCESSORFACTORY_H

#include "../inviwocoredefine.h"
#include "processor.h"
#include "processorfactoryobject.h"
#include "../util/factory.h"

namespace inviwo {

	class IVW_CORE_API ProcessorFactory : public StandardFactory<Processor, ProcessorFactoryObject>
	{
	public:
		ProcessorFactory() = default;
		virtual ~ProcessorFactory() = default;
		bool registerObject(ProcessorFactoryObject* processor) override;
	};
}

#endif