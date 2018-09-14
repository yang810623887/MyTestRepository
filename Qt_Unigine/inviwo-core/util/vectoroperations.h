#ifndef IVW_VECTOROPERATIONS_H
#define IVW_VECTOROPERATIONS_H

#include "../inviwocoredefine.h"
#include "introspection.h"
#include <vector>

namespace inviwo {
	template <typename T>
	class ComparePointers {
	public:
		explicit ComparePointers(const T* ptr) : p(ptr) {}
		bool operator() (const T* rhs) const { return p == rhs; }
	private:
		const T* p;
	};

	template <class T, class U>
	T* getTypeFromVector(std::vector<U*>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			if (auto item = dynamic_cast<T*>(vec[i])) return item;
		}
		return nullptr;
	}

	template <class T, class U>
	T* getTypeFromVector(std::vector<std::unique_ptr<U>>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			if (auto item = dynamic_cast<T*>(vec[i].get())) return item;
		}
		return nullptr;
	}

	template <class T, class U>
	T* getTypeFromVector(const std::vector<U*>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			if (auto item = dynamic_cast<T*>(vec[i])) return item;
		}
		return nullptr;
	}

	template <class T, class U>
	T* getTypeFromVector(const std::vector<std::unique_ptr<U>>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			if (auto item = dynamic_cast<T*>(vec[i].get())) return item;
		}
		return nullptr;
	}

	template <class T, class U>
	bool hasTypeInVector(const std::vector<U> vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			T* item = dynamic_cast<T*>(vec[i]);
			if (item) return true;
		}

		return false;
	}

	struct comparePtr {
		template <typename T>
		bool operator()(const T& a, const T& b) {
			static_assert(util::is_dereferenceable<T>::value, "T has to be dereferenceable");
			return (*a < *b);
		}
	};

	struct equalPtr {
		template <typename T>
		bool operator()(const T& a, const T& b) {
			static_assert(util::is_dereferenceable<T>::value, "T has to be dereferenceable");
			return (*a == *b);
		}
	};
}

#endif