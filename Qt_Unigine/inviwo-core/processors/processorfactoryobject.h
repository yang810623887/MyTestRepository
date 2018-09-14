/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processorfactoryobject
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 16:26:49
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORFACTORYOBJECT_H
#define IVW_PROCESSORFACTORYOBJECT_H

#include "../inviwocoredefine.h"
#include "processorstate.h"
#include "processortags.h"
#include "processorinfo.h"
#include "processortraits.h"


#include <string>

namespace inviwo {

	class Processor;

	class IVW_CORE_API ProcessorFactoryObject
	{
	public:
		ProcessorFactoryObject(const ProcessorInfo info) : info_(info){}
		virtual ~ProcessorFactoryObject() {}

		virtual std::unique_ptr<Processor> create() = 0;

		ProcessorInfo getProcessorInfo() const { return info_; }
		std::string getClassIdentifier() const { return info_.classIdentifier; }
		std::string getDisplayName() const { return info_.displayName; }
		Tags getTags() const { return info_.tags; }
		std::string getCategory() const { return info_.category; }
		CodeState getCodeState() const { return info_.codeState; }

	private:
		const ProcessorInfo info_;
	};

	template <typename T>
	class ProcessorFactoryObjectTemplate : public ProcessorFactoryObject {
	public:
		ProcessorFactoryObjectTemplate()
			: ProcessorFactoryObject(ProcessorTraits<T>::getProcessorInfo()) {}
		virtual ~ProcessorFactoryObjectTemplate() {}

		virtual std::unique_ptr<Processor> create() { return util::make_unique<T>(); }
	};

}
#endif