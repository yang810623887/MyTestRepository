/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: workspacemanager
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-9-3 14:15:39
* --------------------------------------------------------------------------------
* DateTime : 2018/09/03
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORNETWORKMANAGER_H
#define IVW_PROCESSORNETWORKMANAGER_H

#include "../inviwocoredefine.h"
#include "../util/dispatcher.h"
#include "../inviwo.h"
#include "../util/exception.h"

#include <iostream>

namespace inviwo {

	class FactoryBase;
	class InviwoApplication;

	class IVW_CORE_API WorkspaceManager
	{
		using ClearDispatcher = Dispatcher<void()>;
	public:
		WorkspaceManager(InviwoApplication* app);
		~WorkspaceManager();

		/**
		* Clear the current workspace. This will invoke all the clear callback that have been added.
		*/
		void clear();


		/**
		*	Register a factory that should be used by the workspace loading to create items.
		*/
		void registerFactory(FactoryBase* factory);

	private:
		InviwoApplication* app_;
		std::vector<FactoryBase*> registeredFactories_;

		ClearDispatcher clears_;
	};

}
#endif
