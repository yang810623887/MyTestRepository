#ifndef IVW_TEMPLATEPROPERTY_H
#define IVW_TEMPLATEPROPERTY_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "property.h"

namespace inviwo {

	/**
	* \ingroup properties
	* A property holding single value type. The type needs to support copy construction and assignment.
	*/
	template <typename T>
	class TemplateProperty : public Property
	{
	public:
		typedef T value_Type;

		//TemplateProperty(
		//	const std::string& identifier, const std::string& displayName, const T& value = T(),
		//	InvalidationLevel invalidationLevel = InvalidationLevel::InvalidOutput,
		//	PropertySemantics semantics = PropertySemantics::Default);

		//TemplateProperty<T>& operator=(const T& value);

		//virtual TemplateProperty<T>* clone() const override = 0;
		//virtual operator T&();
		//virtual operator const T&() const;

		//virtual ~TemplateProperty() = default;

		//virtual T& get();
		//virtual const T& get() const;
		//virtual void set(const T& value);
		//void set(const TemplateProperty<T>* srcProperty);
		//virtual void set(const Property* srcProperty) override;

		//virtual void setCurrentStateAsDefault() override;
		//virtual void resetToDefaultState() override;

		//virtual void serialize(Serializer& s) const override;
		//virtual void deserialize(Deserializer& d) override;


	};

	//template <typename T>
	//inviwo::TemplateProperty<T>::TemplateProperty(const std::string& identifier, const std::string& displayName, const T& value /*= T()*/, InvalidationLevel invalidationLevel /*= InvalidationLevel::InvalidOutput*/, PropertySemantics semantics /*= PropertySemantics::Default*/)
	//	: Property(identifier, displayName, invalidationLevel, semantics)
	//	, value_("value", value)
	//{

	//}

}

#endif
