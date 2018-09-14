/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processortraits
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 18:26:10
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_PROCESSORTRAITS_H
#define IVW_PROCESSORTRAITS_H

#include "../inviwocoredefine.h"
#include "processorinfo.h"

namespace inviwo {

	namespace detail {

		template<class T>
		class hasProcessorInfo {
			template <class U, class = typename std::enable_if<
				!std::is_member_pointer<decltype(&U::processorInfo_)>::value>::type>

				static std::true_type check(int);
				template<class>
				static std::false_type check(...);

		public:
			static const bool value = decltype(check<T>(0))::value;
		};

		template<typename T, typename std::enable_if<hasProcessorInfo<T>::value, std::size_t>::type = 0>
		ProcessorInfo processorInfo() {
			return T::processorInfo_;
		}

		template<typename T, typename std::enable_if<!hasProcessorInfo<T>::value, std::size_t>::type = 0>
		ProcessorInfo processorInfo() {
			return ProcessorInfo(T::CLASS_IDENTIFIER, T::DISPLAY_NAME, T::CATEGORY, T::CODE_STATE, T::TAGS);
		}
	}

	template <typename T>
	struct ProcessorTraits {
		static ProcessorInfo getProcessorInfo() { return detail::processorInfo<T>(); }
	};

}

#endif
