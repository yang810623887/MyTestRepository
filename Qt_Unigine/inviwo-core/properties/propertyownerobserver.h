#ifndef IVW_PROPERTYOWNEROBSERVER_H
#define IVW_PROPERTYOWNEROBSERVER_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "../util/observer.h"


namespace inviwo {

	class Property;
	class PropertyOwnerObservable;

	class IVW_CORE_API PropertyOwnerObserver : public Observer {
	public:
		friend PropertyOwnerObservable;
		PropertyOwnerObserver() = default;
		virtual ~PropertyOwnerObserver() = default;
	};

	class IVW_CORE_API PropertyOwnerObservable : public Observable<PropertyOwnerObserver> {

	public:
		PropertyOwnerObservable() = default;
		virtual ~PropertyOwnerObservable() = default;
	};
}

#endif
