#ifndef IVW_PROPERTYFACTORYOBJECT_H
#define IVW_PROPERTYFACTORYOBJECT_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "property.h"

namespace inviwo {

	class IVW_CORE_API PropertyFactoryObject
	{
	public:
		PropertyFactoryObject(const std::string& className);
		virtual ~PropertyFactoryObject();

		virtual std::unique_ptr<Property> create(std::string identifier, std::string displayName) = 0;

		std::string getClassIdentifier() const;
	private:
		std::string className_;
	};

}

#endif