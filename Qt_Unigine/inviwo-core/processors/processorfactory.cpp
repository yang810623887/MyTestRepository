#include "processorfactory.h"
#include "../util/stringconversion.h"

namespace inviwo {

	bool ProcessorFactory::registerObject(ProcessorFactoryObject* processor)
	{
		if (!StandardFactory<Processor, ProcessorFactoryObject>::registerObject(processor))
		{
			return false;
		}
		
		/*if (!StandardFactory<Processor, ProcessorFactoryObject>::registerObject(processor))
		{
			return false;
		}*/

		/*if (splitString(processor->getClassIdentifier(), '.').size() < 3)
		{
		}*/



		return true;
	}

}