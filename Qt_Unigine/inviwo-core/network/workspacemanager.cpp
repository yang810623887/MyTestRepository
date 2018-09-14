#include "workspacemanager.h"
#include "../inviwomodule.h"

namespace inviwo {


	WorkspaceManager::WorkspaceManager(InviwoApplication* app) : app_(app){}

	WorkspaceManager::~WorkspaceManager()
	{
	}


	void WorkspaceManager::clear()
	{
		clears_.invoke();
	}

	void WorkspaceManager::registerFactory(FactoryBase* factory)
	{
		registeredFactories_.push_back(factory);
	}

}