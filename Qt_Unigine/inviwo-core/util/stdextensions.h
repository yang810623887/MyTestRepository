/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: stdextensions
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-24 14:53:21
* --------------------------------------------------------------------------------
* DateTime : 2018/08/24
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_STDEXTENSIONS_H
#define IVW_STDEXTENSIONS_H
#include "../inviwocoredefine.h"
#include <memory>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <type_traits>
#include <future>
#include <utility>
#include <tuple>
namespace inviwo {

	namespace util {

		// Since make_unique is a c++14 feature, roll our own in the mean time.
		template <class T, class... Args>
		typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T> >::type make_unique(
			Args&&... args) {
			return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		}
		template <class T>
		typename std::enable_if<std::is_array<T>::value, std::unique_ptr<T> >::type make_unique(
			std::size_t n) {
			typedef typename std::remove_extent<T>::type RT;
			return std::unique_ptr<T>(new RT[n]());
		}


		template <typename T, typename V>
		auto find(T& cont, const V& elem) -> typename T::iterator {
			using std::begin;
			using std::end;
			return std::find(begin(cont), end(cont), elem);
		}

		template <typename T, typename UnaryOperation>
		auto transform(const T& cont, UnaryOperation op)
			-> std::vector<typename std::result_of<UnaryOperation(typename T::value_type)>::type> {

			std::vector<typename std::result_of<UnaryOperation(typename T::value_type)>::type> res;
			res.reserve(cont.size());
			std::transform(cont.begin(), cont.end(), std::back_inserter(res), op);
			return res;
		}

		template <typename Derived, typename Base, typename Del>
		std::unique_ptr<Derived, Del> static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
			auto d = static_cast<Derived*>(p.release());
			return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
		}

		template <typename Derived, typename Base, typename Del>
		std::unique_ptr<Derived, Del> dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
			if (Derived* result = dynamic_cast<Derived*>(p.get())) {
				p.release();
				return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
			}
			return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
		}

		template <typename Derived, typename Base>
		std::unique_ptr<Derived> dynamic_unique_ptr_cast(
			std::unique_ptr<Base, std::default_delete<Base>>&& p) {
			if (Derived* result = dynamic_cast<Derived*>(p.get())) {
				p.release();
				return std::unique_ptr<Derived>(result);
			}
			return std::unique_ptr<Derived>(nullptr);
		}



		template <typename T, typename std::enable_if<
			!std::is_abstract<T>::value && std::is_default_constructible<T>::value,
			int>::type = 0>
			T *defaultConstructType()
		{
			return new T();
		}

		template <typename T, typename std::enable_if<
			std::is_abstract<T>::value || !std::is_default_constructible<T>::value,
			int>::type = 0>
			T *defaultConstructType()
		{
			return nullptr;
		}

		// type trait to check if T is derived from std::basic_string
		namespace detail {
			template <typename T, class Enable = void>
			struct is_string : std::false_type {};

			template <typename... T>
			struct void_helper {
				typedef void type;
			};

			template <typename T>
			struct is_string<T, typename void_helper<typename T::value_type, typename T::traits_type,
				typename T::allocator_type>::type>
				: std::is_base_of<std::basic_string<typename T::value_type, typename T::traits_type,
				typename T::allocator_type>,
				T> {};
		}
		template <typename T>
		struct is_string : detail::is_string<T> {};

		// https://isocpp.org/blog/2015/01/for-each-arg-eric-niebler
		template <class F, class... Args>
		auto for_each_argument(F&& f, Args&&... args) {
			return (void)std::initializer_list<int>{0, (f(std::forward<Args>(args)), 0)...},
				std::forward<F>(f);
		}

		namespace detail {

			template <typename F, typename TupleType, size_t... Is>
			auto for_each_in_tuple_impl(F&& f, std::index_sequence<Is...>, TupleType&& t) {
				return (void)std::initializer_list<int>{0, (f(std::get<Is>(t)), 0)...}, std::forward<F>(f);
			}
			template <typename F, typename TupleType1, typename TupleType2, size_t... Is>
			auto for_each_in_tuple_impl(F&& f, std::index_sequence<Is...>, TupleType1&& t1, TupleType2&& t2) {
				return (void)std::initializer_list<int>{0, (f(std::get<Is>(t1), std::get<Is>(t2)), 0)...},
					std::forward<F>(f);
			}

		}  // namespace detail

		template <typename F, typename TupleType>
		void for_each_in_tuple(F&& f, TupleType&& t) {
			detail::for_each_in_tuple_impl(std::forward<F>(f),
				std::make_index_sequence<std::tuple_size<typename std::remove_reference<TupleType>::type>::value>{},
				std::forward<TupleType>(t));
		}
		template <typename F, typename TupleType1, typename TupleType2>
		void for_each_in_tuple(F&& f, TupleType1&& t1, TupleType2&& t2) {
			detail::for_each_in_tuple_impl(std::forward<F>(f),
				std::make_index_sequence<std::min(std::tuple_size<typename std::remove_reference<TupleType1>::type>::value,
					std::tuple_size<typename std::remove_reference<TupleType2>::type>::value)>{},
				std::forward<TupleType1>(t1),
				std::forward<TupleType2>(t2));
		}
		template <class... Types>
		struct for_each_type;

		template <typename T>
		struct for_each_type<std::tuple<T>> {
			template <class F, class... Args>
			auto operator()(F&& f, Args&&... args) {
#ifdef _WIN32  // TODO: remove win fix when VS does the right thing...
				f.operator() < T > (std::forward<Args>(args)...);
#else
				f.template operator() < T > (std::forward<Args>(args)...);
#endif
				return std::forward<F>(f);
			}
		};

		template <class T, class... Types>
		struct for_each_type<std::tuple<T, Types...>> {
			template <class F, class... Args>
			auto operator()(F&& f, Args&&... args) {
#ifdef _WIN32  // TODO: remove win fix when VS does the right thing...
				f.operator() < T > (std::forward<Args>(args)...);
#else
				f.template operator() < T > (std::forward<Args>(args)...);
#endif
				return for_each_type<std::tuple<Types...>>{}(std::forward<F>(f),
					std::forward<Args>(args)...);
			}
		};

		template <typename T>
		bool has_key(T& map, const typename T::key_type& key) {
			return map.find(key) != map.end();
		}
		template <typename T>
		bool insert_unique(T& map, const typename T::key_type& key, typename T::mapped_type& value) {
			return map.insert(std::make_pair(key, value)).second;
		}

		template <typename T, typename Pred>
		auto erase_remove_if(T& cont, Pred pred)
			-> decltype(std::distance(std::declval<T>().begin(), std::declval<T>().end())) {
			using std::begin;
			using std::end;
			auto it = std::remove_if(begin(cont), end(cont), pred);
			auto nelem = std::distance(it, cont.end());
			cont.erase(it, cont.end());
			return nelem;
		}

		template <typename T, typename Pred>
		size_t map_erase_remove_if(T& cont, Pred pred) {
			using std::begin;
			using std::end;
			size_t removed{ 0 };
			for (auto it = begin(cont); it != end(cont);) {
				if (pred(*it)) {
					it = cont.erase(it);
					removed++;
				}
				else {
					++it;
				}
			}
			return removed;
		}

		template <typename T, typename V>
		bool contains(T& cont, const V& elem) {
			using std::begin;
			using std::end;
			return std::find(begin(cont), end(cont), elem) != end(cont);
		}

	}

}

#endif
