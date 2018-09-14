/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: inviwoapplication
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 13:59:04
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_INVIWOAPPLICATION_H
#define IVW_INVIWOAPPLICATION_H

#include "util/singleton.h"
#include "inviwocoredefine.h"
#include "network/workspacemanager.h"

#include "inviwomodulefactoryobject.h"

#include "util/pathtype.h"
#include "util/threadpool.h"

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <future>
#include <locale>
namespace inviwo {

	class InviwoModule;

	class ProcessorNetwork;
	class ProcessorFactory;
	class PropertyFactory;


	class Settings;

	class IVW_CORE_API InviwoApplication : public Singleton<InviwoApplication>
	{
	public:
		using RegisterModuleFunc =
			std::function<std::vector<std::unique_ptr<InviwoModuleFactoryObject>>()>;

		InviwoApplication();
		InviwoApplication(std::string displayName);
		InviwoApplication(int argc, char** argv, std::string displayName);
		InviwoApplication(const InviwoApplication& rhs) = delete;
		InviwoApplication& operator=(const InviwoApplication& that) = delete;

		virtual ~InviwoApplication();

		virtual void registerModules(RegisterModuleFunc func);

		// Factory getters
		ProcessorFactory* getProcessorFactory() const;
//		PropertyFactory* getPropertyFactory() const;
		/**
		* Get basePath + pathType + suffix.
		* @see PathType
		* @param pathType Enum for type of path
		* @param suffix Path extension
		* @param createFolder whether to create the folder if it does not exist.
		* @return basePath +  pathType + suffix
		*/
		std::string getPath(PathType pathType, const std::string& suffix = "",
			const bool& createFolder = false);

		void registerModule(std::unique_ptr<InviwoModule> module);
		const std::vector<std::unique_ptr<InviwoModule>>& getModules() const;

		template <class T>
		T* getModuleByType() const;

		void setProgressCallback(std::function<void(std::string)> progressCallback);


		ProcessorNetwork* getProcessorNetwork();

		WorkspaceManager* getWorkspaceManager();

		//template <class T>
		//T* getSettingsByType();

		std::vector<Settings*> getModuleSettings(size_t startIdx = 0);

	protected:
		virtual void printApplicationInfo();
		void postProgress(std::string progress);
		virtual void resizePool(size_t newSize);


		std::vector<std::unique_ptr<InviwoModuleFactoryObject>> modulesFactoryObjects_;
		std::vector<std::unique_ptr<InviwoModule>> modules_;
//		std::unique_ptr<PropertyFactory> propertyFactory_;

		std::unique_ptr<ProcessorNetwork> processorNetwork_;

		std::unique_ptr<WorkspaceManager> workspaceManager_;

		std::string displayName_;

		std::function<void(std::string)> progressCallback_;
		ThreadPool pool_;

		std::unique_ptr<ProcessorFactory> processorFactory_;
	};

	//template <class T>
	//T* InviwoApplication::getSettingsByType() {
	//	auto settings = getModuleSettings();
	//	return getTypeFromVector<T>(settings);
	//}

	template <class T>
	T* inviwo::InviwoApplication::getModuleByType() const
	{
		return getTypeFromVector<T>(modules_);
	}

	//inline PropertyFactory* InviwoApplication::getPropertyFactory() const {
	//	return propertyFactory_.get();
	//}

	inline ProcessorFactory* InviwoApplication::getProcessorFactory() const {
		return processorFactory_.get();
	}

}
#endif