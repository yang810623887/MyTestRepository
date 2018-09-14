#ifndef IVW_SETTINGS_H
#define IVW_SETTINGS_H

#include "../../inviwocoredefine.h"
#include "../../inviwo.h"
#include "../../inviwomodule.h"
#include "../../properties/propertyowner.h"

namespace inviwo {
	class IVW_CORE_API Settings : public PropertyOwner
	{
	public:
		Settings(const std::string &id = "");
		virtual ~Settings();

		virtual void addProperty(Property* property, bool owner = true) override;
		virtual void addProperty(Property& property) override;

		virtual std::string getIdentifier();

	protected:
		std::string identifier_;
		bool isDeserializing_;
	};

}

#endif