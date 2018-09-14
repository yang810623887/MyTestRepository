/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: propertyobserver
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 14:44:11
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROPERTYOBSERVER_H
#define IVW_PROPERTYOBSERVER_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "../util/observer.h"

namespace inviwo {
 
 	class IVW_CORE_API PropertyObserver : public Observer
 	{
 	public:
 		PropertyObserver() = default;
 		virtual ~PropertyObserver() = default;
 
		//virtual void onSetIdentifier(const std::string& identifier);
		//virtual void onSetDisplayName(const std::string& displayName);
		//virtual void onSetSemantics(const PropertySemantics& semantics);
		//virtual void onSetReadOnly(bool readonly);
		//virtual void onSetVisible(bool visible);
		//virtual void onSetUsageMode(UsageMode usageMode);
 	};
	class IVW_CORE_API PropertyObservable : public Observable<PropertyObserver>
	{
	protected:
		PropertyObservable() = default;
		/*void notifyObserversOnSetIdentifier(const std::string& identifier);
		void notifyObserversOnSetDisplayName(const std::string& displayName);
		void notifyObserversOnSetSemantics(const PropertySemantics& semantics);
		void notifyObserversOnSetReadOnly(bool readonly);
		void notifyObserversOnSetVisible(bool visible);
		void notifyObserversOnSetUsageMode(UsageMode usageMode);*/
	};

}


#endif
