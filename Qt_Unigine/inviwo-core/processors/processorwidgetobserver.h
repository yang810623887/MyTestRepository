/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processorwidgetobserver
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2017-8-31 14:15:52
* --------------------------------------------------------------------------------
* DateTime : 2017/08/31
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORWIDGETOBSERVER_H
#define IVW_PROCESSORWIDGETOBSERVER_H

#include "../inviwocoredefine.h"
#include "../util/observer.h"

namespace inviwo {

	class ProcessorWidget;
	class ProcessorWidgetObservable;

	class IVW_CORE_API ProcessorWidgetObserver : public Observer
	{
		
	public:
		friend ProcessorWidgetObservable;
		ProcessorWidgetObserver() = default;
		virtual ~ProcessorWidgetObserver() = default;

		virtual void onProcessorWidgetShow(ProcessorWidget*);
		virtual void onProcessorWidgetHide(ProcessorWidget*);
	};

	class IVW_CORE_API ProcessorWidgetObservable : public Observable<ProcessorWidgetObserver> {

	public:
		ProcessorWidgetObservable() = default;
		virtual ~ProcessorWidgetObservable() = default;

		void notifyObserversAboutShow(ProcessorWidget *p);
		void notifyObserversAboutHide(ProcessorWidget *p);
	};
}

#endif