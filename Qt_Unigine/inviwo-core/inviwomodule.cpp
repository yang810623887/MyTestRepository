#include "inviwomodule.h"
#include "util/filesystem.h"
#include "../inviwo-core/util/settings/settings.h"

#include "../build/_generated/inviwomodulespaths.h"


namespace inviwo {

	InviwoModule::InviwoModule(InviwoApplication* app, const std::string& identifier)
		: app_(app)
		, identifier_(identifier){}

	InviwoModule::~InviwoModule()
	{

	}

	std::string InviwoModule::getIdentifier() const
	{
		return identifier_;
	}

	std::string InviwoModule::getDescription() const
	{
		//for (auto &item : app_->getMou)
		//{
		//}
		return "";
	}

	std::string InviwoModule::getPath() const
	{
		std::string moduleNameLowerCase = toLower(getIdentifier());

		const auto defaultPath = filesystem::findBasePath() + "/modules/" + moduleNameLowerCase;

		if (filesystem::directoryExists(defaultPath))
		{
			return defaultPath;
		}
		else
		{
			for (auto &elem : inviwoModulePaths_)
			{
				const auto path = elem + "/" + moduleNameLowerCase;
				if (filesystem::directoryExists(path))
				{
					return path;
				}
			}
		}
		return defaultPath;
	}

	std::string InviwoModule::getPath(ModulePath type) const
	{
		std::string path = getPath();
		switch (type) {
		case ModulePath::Data:               return path + "/data";
		case ModulePath::Images:             return path + "/data/images";
		case ModulePath::PortInspectors:     return path + "/data/portinspectors";
		case ModulePath::Scripts:            return path + "/data/scripts";
		case ModulePath::Volumes:            return path + "/data/volumes";
		case ModulePath::Workspaces:         return path + "/data/workspaces";
		case ModulePath::Docs:               return path + "/docs";
		case ModulePath::Tests:              return path + "/tests";
		case ModulePath::TestImages:         return path + "/tests/images";
		case ModulePath::TestVolumes:        return path + "/tests/volumes";
		case ModulePath::UnitTests:          return path + "/tests/unittests";
		case ModulePath::RegressionTests:    return path + "/tests/regression";
		case ModulePath::GLSL:               return path + "/glsl";
		case ModulePath::CL:                 return path + "/cl";
		default:                             return path;
		}
	}

	int InviwoModule::getVersion() const
	{
		return 0;
	}

	const std::vector<ProcessorFactoryObject*> InviwoModule::getProcessors() const
	{
		return uniqueToPtr(processors_);
	}

	const std::vector<Settings*> InviwoModule::getSettings() const
	{
		return uniqueToPtr(settings_);
	}

	void InviwoModule::registerSettings(std::unique_ptr<Settings> settings)
	{
		settings_.push_back(std::move(settings));
	}

}