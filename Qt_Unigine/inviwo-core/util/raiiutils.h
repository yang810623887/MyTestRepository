/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: raiiutils
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-23 14:46:38
* --------------------------------------------------------------------------------
* DateTime : 2018/08/23
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_RAIIUTILS_H
#define IVW_RAIIUTILS_H

#include "../inviwocoredefine.h"
#include <functional>
namespace inviwo {

	namespace util {

		class /*IVW_CORE_API*/ KeepTrueWhileInScope {

		public:
			KeepTrueWhileInScope(bool* b)
				: variable_(b)
			{
				if (variable_)
					(*variable_) = true;
			}
			~KeepTrueWhileInScope() { if (variable_) (*variable_) = false; }
		private:
			bool* variable_;
		};

		struct IVW_CORE_API OnScopeExit {
			typedef std::function<void(void)> ExitAction;

			OnScopeExit() = delete;
			OnScopeExit(OnScopeExit const&) = delete;
			OnScopeExit& operator=(OnScopeExit const& that) = delete;

			OnScopeExit(OnScopeExit&& rhs) : action_(std::move(rhs.action_)) { rhs.action_ = nullptr; };
			OnScopeExit& operator=(OnScopeExit&& that) {
				if (this != &that) {
					action_ = nullptr;
					std::swap(action_, that.action_);
				}
				return *this;
			}

			OnScopeExit(ExitAction action) try : action_(action) {
			}
			catch (...) {
				action();
			}
			~OnScopeExit() {
				if (action_) action_();
			}

			void setAction(ExitAction action = nullptr) { action_ = action; }
			void release() { setAction(); }
		private:
			ExitAction action_;
		};
	}

}

#endif