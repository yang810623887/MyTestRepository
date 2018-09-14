#ifndef IVW_PROPERTYOWNER_H
#define IVW_PROPERTYOWNER_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "propertyownerobserver.h"
#include "property.h"

namespace inviwo {

	class IVW_CORE_API PropertyOwner : public PropertyOwnerObservable
	{
	public:
		using iterator = std::vector<Property*>::iterator;
		using const_iterator = std::vector<Property*>::const_iterator;

		PropertyOwner();
		PropertyOwner(const PropertyOwner& rhs);
//		PropertyOwner& operator=(const PropertyOwner& that);
		virtual ~PropertyOwner() = default;

		virtual void addProperty(Property* property, bool owner = true);
		virtual void addProperty(Property& property);

		const std::vector<Property*>& getProperties() const;

	protected:
		// Add the properties belonging the the property owner
		// PropertyOwner do not assume owner ship here since in the most common case these are
		// pointers to members of derived classes.
		std::vector<Property*> properties_;
	};

}

#endif
