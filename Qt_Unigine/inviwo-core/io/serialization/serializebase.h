#ifndef IVW_SERIALIZE_BASE_H
#define IVW_SERIALIZE_BASE_H

#include "ticpp.h"
#include "../../inviwocoredefine.h"
#include "serializeconstants.h"


#include "../../util/factory.h"
#include <map>

// include glm
#include "../../glm.h"

namespace inviwo {

	template <typename T>
	struct ElementIdentifier {
		virtual ~ElementIdentifier() = default;
		virtual void setKey(TxElement*) = 0;
		virtual bool operator()(const T* elem) const = 0;
	};

	template <typename T>
	struct StandardIdentifier : public ElementIdentifier<T> {
		typedef std::string(T::*funcPtr)() const;

		StandardIdentifier(std::string key = "identifier", funcPtr ptr = &T::getIdentifier)
			: ptr_(ptr), key_(key) {}

		virtual void setKey(TxElement* node) { identifier_ = node->GetAttributeOrDefault(key_, ""); }
		virtual bool operator()(const T* elem) const { return identifier_ == (*elem.*ptr_)(); }

	private:
		funcPtr ptr_;
		std::string key_;
		std::string identifier_;
	};

	enum class SerializationTarget { Node, Attribute };

	class NodeSwitch;
	class Serializable;

	class IVW_CORE_API SerializeBase
	{
	public:
		SerializeBase(bool allowReference = true);

		/**
		* \brief Base class for Serializer and Deserializer.
		*
		* This class consists of features that are common to both serializer
		* and de-serializer. Some of them are reference data manager,
		* (ticpp::Node) node switch and factory registration.
		*
		* @param fileName full path to xml file (for reading or writing).
		* @param allowReference disables or enables reference management schemes.
		*/
		SerializeBase(std::string fileName, bool allowReference = true);

		/**
		* \brief Base class for Serializer and Deserializer.
		*
		* This class consists of features that are common to both serializer
		* and de-serializer. Some of them are reference data manager,
		* (ticpp::Node) node switch and factory registration.
		*
		* @param stream containing all xml data (for reading).
		* @param path A path that will be used to decode the location of data during deserialization.
		* @param allowReference disables or enables reference management schemes.
		*/
		SerializeBase(std::istream& stream, const std::string& path, bool allowReference = true);

		SerializeBase(const SerializeBase& rhs) = delete;
		SerializeBase(SerializeBase&& rhs) = default;
		SerializeBase& operator=(const SerializeBase&) = delete;
		SerializeBase& operator=(SerializeBase&&) = default;

		virtual ~SerializeBase() = default;

		/**
		* \brief gets the xml file name.
		*/
		virtual const std::string& getFileName() const;

		/**
		* \brief Checks whether the given type is a primitive type.
		*
		* return true if type is one of following type:
		* bool, char, signed int, unsigned int, float, double, long double, std::string
		*
		* @param type can be one of  bool, char, signed int, unsigned int, float, double, long double, std::string
		* @return true or false
		*/
		bool isPrimitiveType(const std::type_info& type) const;

		struct IVW_CORE_API ReferenceData {
			TxElement* node_; //Ticpp Node element.
			bool isPointer_; //Used to differentiate pointer and object.
		};

		using RefDataPair = std::pair<const void*, SerializeBase::ReferenceData>;
		using RefMap = std::multimap<const void*, ReferenceData>;

		class IVW_CORE_API ReferenceDataContainer {
		public:
			ReferenceDataContainer() = default;
			ReferenceDataContainer(const ReferenceDataContainer&) = delete;
			ReferenceDataContainer(ReferenceDataContainer&&) = default;
			ReferenceDataContainer& operator=(const ReferenceDataContainer&) = delete;
			ReferenceDataContainer& operator=(ReferenceDataContainer&&) = default;
			~ReferenceDataContainer() = default;

			size_t insert(const void* data, TxElement* node, bool isPointer = true);
			size_t find(const void* data);
			void* find(const std::string& key, const std::string& reference_or_id);
			TxElement* nodeCopy(const void* data);
			void setReferenceAttributes();

		private:
			RefMap referenceMap_;
			int referenceCount_ = 0;
		};

		static std::string nodeToString(const TxElement& node);

	protected:
		friend class NodeSwitch;

		std::string fileName_;
		TxDocument doc_;
		TxElement* rootElement_;
		bool allowRef_;
		bool retrieveChild_;
		ReferenceDataContainer refDataContainer_;
	};

	class IVW_CORE_API NodeSwitch {
	public:
		/**
		* \brief NodeSwitch helps track parent node during recursive/nested function calls.
		*
		* @param serializer reference to serializer or deserializer
		* @param node //Parent (Ticpp Node) element.
		*/
		NodeSwitch(SerializeBase& serializer, TxElement* node, bool retrieveChild = true);

		/**
		* \brief NodeSwitch helps track parent node during recursive/nested function calls.
		*
		* @param serializer reference to serializer or deserializer
		* @param key the child to switch to.
		*/
		NodeSwitch(SerializeBase& serializer, const std::string& key, bool retrieveChild = true);

		/**
		* \brief Destructor
		*/
		~NodeSwitch();

		operator bool() const;

	private:
		SerializeBase& serializer_;  // reference to serializer or deserializer
		TxElement* storedNode_;  // Parent (Ticpp Node) element.
		bool storedRetrieveChild_;
	};
}
#endif