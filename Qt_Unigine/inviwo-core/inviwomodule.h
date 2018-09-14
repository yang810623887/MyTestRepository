/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: inviwomodule
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2017-9-3 10:17:05
* --------------------------------------------------------------------------------
* DateTime : 2017/09/03
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_INVIWOMODULE_H
#define IVW_INVIWOMODULE_H

#include "inviwocoredefine.h"
#include "inviwoapplication.h"
#include "processors/processorfactoryobject.h"
#include "processors/processorfactory.h"

namespace inviwo {

	class Settings;

	enum class ModulePath {
		Data,               // /data
		Images,             // /data/images
		PortInspectors,     // /data/portinspectors
		Scripts,            // /data/scripts
		Volumes,            // /data/volumes
		Workspaces,         // /data/workspaces
		Docs,               // /docs
		Tests,              // /tests
		TestImages,         // /tests/images
		TestVolumes,        // /tests/volumes
		UnitTests,          // /tests/unittests
		RegressionTests,    // /tests/regression
		GLSL,               // /glsl
		CL                  // /cl
	};

	class IVW_CORE_API InviwoModule
	{
	public:
		InviwoModule(InviwoApplication* app, const std::string& identifier);
		InviwoModule(const InviwoModule&) = delete;
		InviwoModule& operator=(const InviwoModule&) = delete;
		virtual ~InviwoModule();

		/**
		* \brief Get module identifier, i.e the module folder name.
		*/
		std::string getIdentifier() const;

		/**
		* Override to provide a description of the module
		*/
		virtual std::string getDescription() const;

		/**
		* Get the path to this module directory.
		* For instance: C:/inviwo/modules/mymodule/
		* @note Assumes that getIdentifier() returns the module folder name.
		*       The folder name should always be lower case.
		* @note The returned directory might not exist in the case that the app is
		*       deployed and the module does not contain any resources.
		* @return std::string Path to module directory
		*/
		virtual std::string getPath() const;
		std::string getPath(ModulePath type) const;

		/**
		* Returns the module version. This is used for converting old processor networks in connection
		* with the getConverter function. By default it will return 0. Overload this function to return
		* a larger value when you need to update the module version.
		*/
		virtual int getVersion() const;

		const std::vector<ProcessorFactoryObject*> getProcessors() const;

		const std::vector<Settings*> getSettings() const;
	protected:

		template <typename T>
		void registerProcessor();

		void registerSettings(std::unique_ptr<Settings> settings);

		InviwoApplication* app_;  // reference to the app that we belong to

	private:

		const std::string identifier_;  ///< Module folder name


		template <typename T>
		const std::vector<T*> uniqueToPtr(const std::vector<std::unique_ptr<T>>& v) const {
			std::vector<T*> res;
			for (auto& elem : v) res.push_back(elem.get());
			return res;
		}

		


		std::vector<std::unique_ptr<ProcessorFactoryObject>> processors_;

		std::vector<std::unique_ptr<Settings>> settings_;
	};

	template <typename T>
	void InviwoModule::registerProcessor() {
		auto processor = util::make_unique<ProcessorFactoryObjectTemplate<T>>();
		//if (app_->getProcessorFactory()->registerObject(processor.get())) 
		{
			processors_.push_back(std::move(processor));
		}
	}

}
#endif