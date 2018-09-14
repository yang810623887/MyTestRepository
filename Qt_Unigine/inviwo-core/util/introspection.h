#ifndef IVW_INTROSPECTION_H
#define IVW_INTROSPECTION_H

#include "../inviwocoredefine.h"
#include "../inviwo-core/glm.h"

#include <type_traits>
#include <iostream>

namespace inviwo {

	namespace util {
		template <class... >
		using void_t = void;

		template <class T>
		class has_class_identifier {
			template <class U, class = typename std::enable_if<
				!std::is_member_pointer<decltype(&U::CLASS_IDENTIFIER)>::value>::type>
				static std::true_type check(int);
			template <class>
			static std::false_type check(...);

		public:
			static const bool value = decltype(check<T>(0))::value;
		};

		template <typename T,
			typename std::enable_if<util::has_class_identifier<T>::value, std::size_t>::type = 0>
			std::string class_identifier() {
			return T::CLASS_IDENTIFIER;
		}
		template <typename T,
			typename std::enable_if<!util::has_class_identifier<T>::value, std::size_t>::type = 0>
			std::string class_identifier() {
			return std::string{};
		}

		template <class T>
		class has_color_code {
			template <class U, class = typename std::enable_if<
				!std::is_member_pointer<decltype(&U::COLOR_CODE)>::value>::type>
				static std::true_type check(int);
			template <class>
			static std::false_type check(...);

		public:
			static const bool value = decltype(check<T>(0))::value;
		};


		template <typename T,
			typename std::enable_if<util::has_color_code<T>::value, std::size_t>::type = 0>
			uvec3 color_code() {
			return T::COLOR_CODE;
		}
		template <typename T,
			typename std::enable_if<!util::has_color_code<T>::value, std::size_t>::type = 0>
			uvec3 color_code() {
			return uvec3(0);
		}

		template <typename T,
			typename std::enable_if<util::has_color_code<T>::value, std::size_t>::type = 0>
			uvec3 color_code() {
			return T::COLOR_CODE;
		}
		template <typename T,
			typename std::enable_if<!util::has_color_code<T>::value, std::size_t>::type = 0>
			uvec3 color_code() {
			return uvec3(0);
		}

		template <typename C>
		class has_data_info {
			template <typename T>
			static auto check(int) ->
				typename std::is_same<decltype(std::declval<T>().getDataInfo()), std::string>::type;

			template <typename T>
			static std::false_type check(...);
		public:
			static const bool value = decltype(check<C>(0))::value;
		};

		template <typename T,
			typename std::enable_if<util::has_data_info<T>::value, std::size_t>::type = 0>
			std::string data_info(const T* data) {
			return data->getDataInfo();
		}
		template <typename T,
			typename std::enable_if<!util::has_data_info<T>::value, std::size_t>::type = 0>
			std::string data_info(const T*) {
			return "";
		}

		template <class T>
		class is_stream_insertable {
			template <typename U, class = typename std::enable_if<std::is_convertible<
				decltype(std::declval<std::ostream&>() << std::declval<U>()),
				std::ostream&>::value>::type>
				static std::true_type check(int);
			template <class>
			static std::false_type check(...);

		public:
			static const bool value = decltype(check<T>(0))::value;
		};

		// primary template handles types that do not support dereferencing:
		template< class, class = void_t<> >
		struct is_dereferenceable : std::false_type { };
		// specialization recognizes types that do support dereferencing:
		template< class T >
		struct is_dereferenceable<T, void_t<decltype(*std::declval<T>())>> : std::true_type { };
	}
}

#endif