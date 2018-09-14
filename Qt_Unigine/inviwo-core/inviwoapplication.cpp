#include "inviwoapplication.h"
#include "network/processornetwork.h"
#include "util/filesystem.h"
#include "../inviwo-core/properties/propertyfactory.h"
#include "../inviwo-core/util/settings/settings.h"

#include "inviwomodule.h"
#include "inviwocore.h"



namespace inviwo {
	InviwoApplication::InviwoApplication() : InviwoApplication(0, nullptr, "Inviwo"){}

	InviwoApplication::InviwoApplication(std::string displayName)
		: InviwoApplication(0, nullptr, displayName){}

	InviwoApplication::InviwoApplication(int argc, char** argv, std::string displayName)
		: displayName_(displayName)
		, progressCallback_()
		, pool_(0, []() {}, []() { })
		, workspaceManager_{ util::make_unique<WorkspaceManager>(this) }
		//, propertyFactory_{ util::make_unique<PropertyFactory>() }
		, modules_()
	{
		init(this);

		auto ivwCore = util::make_unique<InviwoCore>(this);
		registerModule(std::move(ivwCore));
	}



	std::string InviwoApplication::getPath(PathType pathType, const std::string& suffix, const bool& createFolder )
	{
		return filesystem::getPath(pathType, suffix, createFolder);
	}

	void InviwoApplication::registerModule(std::unique_ptr<InviwoModule> module)
	{
		modules_.push_back(std::move(module));
	}

	const std::vector<std::unique_ptr<InviwoModule>>& InviwoApplication::getModules() const
	{
		return modules_;
	}

	void InviwoApplication::setProgressCallback(std::function<void(std::string)> progressCallback)
	{
		progressCallback_ = progressCallback;
	}

	ProcessorNetwork* InviwoApplication::getProcessorNetwork()
	{
		return processorNetwork_.get();
	}

	WorkspaceManager* InviwoApplication::getWorkspaceManager()
	{
		return workspaceManager_.get();
	}

	std::vector<Settings*> InviwoApplication::getModuleSettings(size_t startIdx /*= 0*/)
	{
		std::vector<Settings*> allModuleSettings;

		for (size_t i = startIdx; i < modules_.size(); i++) {
			auto modSettings = modules_[i]->getSettings();
			allModuleSettings.insert(allModuleSettings.end(), modSettings.begin(), modSettings.end());
		}

		return allModuleSettings;
	}

	InviwoApplication::~InviwoApplication()
	{
		resizePool(0);
	}

	void InviwoApplication::registerModules(RegisterModuleFunc regModuleFunc)
	{
		printApplicationInfo();

		modulesFactoryObjects_ = regModuleFunc();
		std::vector<std::string> failed;
		auto checkdepends = [&](const std::vector<std::string>& deps)
		{
			for (const auto& dep : deps)
			{
				auto it = util::find(failed, dep);
				if (it != failed.end())
				{
					return it;
				}
			}
			return failed.end();
		};

		for (auto& moduleObj : modulesFactoryObjects_)
		{
			postProgress("Loading module: " + moduleObj->name_);
			try
			{
				auto it = checkdepends(moduleObj->depends_);
				if (it == failed.end())
				{
					registerModule(moduleObj->create(this));
				}
			}
			catch (const std::exception&)
			{

			}
		}
	}

	void InviwoApplication::printApplicationInfo()
	{

	}

	void InviwoApplication::postProgress(std::string progress)
	{
		if (progressCallback_)
		{
			progressCallback_(progress);
		}
	}

	void InviwoApplication::resizePool(size_t newSize)
	{
		size_t size = pool_.trySetSize(newSize);
	}

}