#ifndef IVW_BASEOPTIONPROPERTY_H
#define IVW_BASEOPTIONPROPERTY_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "property.h"


namespace inviwo {

	class IVW_CORE_API BaseOptionProperty : public Property {

	};

	template <typename T>
	class OptionPropertyOption// : public Serializable 
	{
	public:
		T value_;
	};

	template <typename T>
	class TemplateOptionProperty : public BaseOptionProperty {

	public:
		T getSelectedValue() const;

	protected:
		size_t selectedIndex_;
		std::vector<OptionPropertyOption<T>> options_;

	};

	template <typename T>
	T TemplateOptionProperty<T>::getSelectedValue() const {
		return options_[selectedIndex_].value_;
	}

	//template <typename T>
	//bool TemplateOptionProperty<T>::setSelectedValue(T val) {
	//	auto it = util::find_if(options_, MatchValue<T>(val));
	//	if (it != options_.end()) {
	//		size_t dist = std::distance(options_.begin(), it);
	//		if (selectedIndex_ != dist) {
	//			selectedIndex_ = dist;
	//			propertyModified();
	//		}
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//}
}

#endif
