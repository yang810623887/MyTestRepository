#include "processorwidgetobserver.h"
#include "processorwidget.h"

namespace inviwo {

	void ProcessorWidgetObserver::onProcessorWidgetShow(ProcessorWidget*)
	{

	}

	void ProcessorWidgetObserver::onProcessorWidgetHide(ProcessorWidget*)
	{

	}

	void ProcessorWidgetObservable::notifyObserversAboutShow(ProcessorWidget *p)
	{
		forEachObserver([&](ProcessorWidgetObserver *o)
		{
			o->onProcessorWidgetShow(p);
		});
	}

	void ProcessorWidgetObservable::notifyObserversAboutHide(ProcessorWidget *p)
	{
		forEachObserver([&](ProcessorWidgetObserver* o) 
		{
			o->onProcessorWidgetHide(p); 
		});
	}

}