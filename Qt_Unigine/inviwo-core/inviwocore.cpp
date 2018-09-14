#include "inviwocore.h"
#include "util/filesystem.h"

//Utilizes
#include "util/settings/systemsettings.h"

namespace inviwo {




	InviwoCore::InviwoCore(InviwoApplication *app)
		: InviwoModule(app, "Core")
	{
		registerSettings(util::make_unique<SystemSettings>());
		//registerSettings(util::make_unique<LinkSettings>("Link Settings", app_->getPropertyFactory()));
	}

	std::string InviwoCore::getPath() const
	{
		return filesystem::findBasePath();
	}

}