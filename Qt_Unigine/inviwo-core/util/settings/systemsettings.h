#ifndef IVW_SYSTEMSETTINGS_H
#define IVW_SYSTEMSETTINGS_H

#include "settings.h"
#include "../../properties/optionproperty.h"
#include "../../properties/boolproperty.h"
#include "../../properties/ordinalproperty.h"
#include "../../properties/buttonproperty.h"
#include "../../properties/compositeproperty.h"

namespace inviwo {
	class IVW_CORE_API SystemSettings : public Settings
	{
	public:
		SystemSettings();

		TemplateOptionProperty<UsageMode> applicationUsageMode_;
	};
}

#endif
