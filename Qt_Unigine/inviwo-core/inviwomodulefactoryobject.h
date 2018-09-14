#ifndef IVW_INVIWOMODULEFACTORYOBJECT_H
#define IVW_INVIWOMODULEFACTORYOBJECT_H

#include "inviwocoredefine.h"
#include "inviwo.h"
#include "util/stdextensions.h"


namespace inviwo {

	class InviwoModule;
	class InviwoApplication;

	class IVW_CORE_API InviwoModuleFactoryObject
	{
	public:
		InviwoModuleFactoryObject(const std::string& name, const std::string& description,
			std::vector<std::string> depends);
		virtual ~InviwoModuleFactoryObject();

		virtual std::unique_ptr<InviwoModule> create(InviwoApplication* app) = 0;

		const std::string name_;
		const std::string description_;
		const std::vector<std::string> depends_;
	};

	template <typename T>
	class InviwoModuleFactoryObjectTemplate : public InviwoModuleFactoryObject {
	public:
		InviwoModuleFactoryObjectTemplate(const std::string& name, const std::string& description,
			std::vector<std::string> depends);

		virtual std::unique_ptr<InviwoModule> create(InviwoApplication* app) override {
			return util::make_unique<T>(app);
		}
	};

	template <typename T>
	inviwo::InviwoModuleFactoryObjectTemplate<T>::InviwoModuleFactoryObjectTemplate(
		const std::string& name, const std::string& description, std::vector<std::string> depends)
		: InviwoModuleFactoryObject(name, description, depends) {}


}
#endif