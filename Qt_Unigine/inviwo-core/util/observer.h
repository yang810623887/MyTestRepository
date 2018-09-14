#ifndef IVW_OBSERVER_H
#define IVW_OBSERVER_H

#include "../inviwocoredefine.h"
#include <unordered_set>
#include <algorithm>
#include <functional>
namespace inviwo {

	
	class IVW_CORE_API Observer
	{
		friend class ObservableInterface;
	public:
		Observer() = default;
		Observer(const Observer& other);
		Observer(Observer&& other);
		Observer& operator=(Observer&& other);
		Observer& operator=(const Observer& other);
		virtual ~Observer();

		void removeObservation(ObservableInterface* observable);

		void removeObservations();

	protected:
		void addObservation(ObservableInterface* observable);
		
		using ObservableSet = std::unordered_set<ObservableInterface*>;
		ObservableSet observables_;

	private:
		void addObservationInternal(ObservableInterface* observable);

		void removeObservationInternal(ObservableInterface* observable);
	};


	class IVW_CORE_API ObservableInterface {
		friend class Observer;
	public:
		virtual ~ObservableInterface() = default;

		virtual void startBlockingNotifications() = 0;
		virtual void stopBlockingNotifications() = 0;

	protected:
		virtual void addObserver(Observer* observer) = 0;
		virtual void removeObserver(Observer* observer) = 0;
		virtual void removeObservers() = 0;

		void addObservationHelper(Observer* observer);
		void removeObservationHelper(Observer* observer);

	private:
		virtual void addObserverInternal(Observer* observer) = 0;
		virtual void removeObserverInternal(Observer* observer) = 0;
	};


	template <typename T>
	class Observable : public ObservableInterface {
	public:
		Observable() = default;
		Observable(const Observable<T>& other);
		Observable(Observable<T>&& other);
		Observable<T>& operator = (Observable<T>&& other);
		Observable<T>& operator = (const Observable<T>& other);

		virtual ~Observable();

		void addObserver(T* observer);
		void removeObserver(T* observer);

		virtual void startBlockingNotifications() override final;
		virtual void stopBlockingNotifications() override final;

	protected:
		template <typename C>
		void forEachObserver(C callback);

	private:
		using ObserverSet = std::unordered_set<T*>;
		ObserverSet observers_;

		// invocationCount counts how may time we have called forEachObserver
		// Add we will only add and remove observers when that it is zero to avoid
		// Invalidation the iterators. This is needed since a observer might remove it
		// self in the on... callback.
		size_t invocationCount_ = 0;
		ObserverSet toAdd_;
		ObserverSet toRemove_;

		size_t notificationsBlocked_ = 0;

		virtual void addObserver(Observer* observer) override;
		virtual void removeObserver(Observer* observer) override;
		virtual void removeObservers() override;
		virtual void addObserverInternal(Observer* observer) override;
		virtual void removeObserverInternal(Observer* observer) override;
	};

	template <typename T>
	Observable<T>::Observable(const Observable<T>& rhs)
	{
		for (auto elem : rhs.observers_)
		{
			addObserver(elem);
		}
	}

	template <typename T>
	Observable<T>::Observable(Observable<T>&& rhs)
	{
		for (auto elem : rhs.observers_)
		{
			addObserver(elem);
		}
		rhs.removeObservers();
	}

	template <typename T>
	Observable<T>& inviwo::Observable<T>::operator=(const Observable<T>& that)
	{
		if (this != &that)
		{
			removeObservers();
			for (auto elem : that.observers_)
			{
				addObserver(elem);
			}
		}
		return *this;
	}
	template <typename T>
	Observable<T>& inviwo::Observable<T>::operator=(Observable<T>&& that) {
		if (this != &that) {
			removeObservers();
			for (auto elem : that.observers_) addObserver(elem);
			{
				that.removeObservers();
			}	
		}
		return *this;
	}

	template <typename T>
	Observable<T>::~Observable() {
		removeObservers();
	}

	template <typename T>
	void Observable<T>::removeObservers() {
		for (auto o : observers_)
		{
			removeObservationHelper(o);
			observers_.clear();
		}
	}

	template <typename T>
	void Observable<T>::addObserver(T* observer) {
		if (invocationCount_ == 0)
		{
			auto inserted = observers_.insert(observer);
			if (inserted.second)
			{
				addObservationHelper(observer);
			}
		}
		else
		{
			toAdd_.insert(observer);
			addObservationHelper(observer);
		}
	}

	template <typename T>
	void Observable<T>::removeObserver(T* observer)
	{
		if (invocationCount_ == 0)
		{
			if (observers_.erase(observer) > 0)
			{
				removeObservationHelper(observer);
			}
		} 
		else
		{
			toRemove_.insert(observer);
			removeObservationHelper(observer);
		}
	}

	template <typename T>
	void Observable<T>::startBlockingNotifications()
	{
		++notificationsBlocked_;
	}

	template <typename T>
	void Observable<T>::stopBlockingNotifications() {
		--notificationsBlocked_;
	}

	template <typename T>
	template <typename C>
	void Observable<T>::forEachObserver(C callback) {
		if (notificationsBlocked_ > 0) return;
		++invocationCount_;
		for (auto o : observers_)
		{
			callback(o);
		}
		--invocationCount_;

		if (invocationCount_ == 0)
		{
			for (auto o : toAdd_)
			{
				observers_.insert(o);
			}
			toAdd_.clear();
			for (auto o : toRemove_)
			{
				observers_.erase(o);
			}
			toRemove_.clear();
		}
	}

	template <typename T>
	void Observable<T>::addObserver(Observer* observer)
	{
		addObserver(static_cast<T*>(observer));
	}

	template <typename T>
	void Observable<T>::removeObserver(Observer* observer)
	{
		removeObserver(static_cast<T*>(observer));
	}

	template <typename T>
	void inviwo::Observable<T>::addObserverInternal(Observer* observer) {
		if(invocationCount_ == 0)
		{
			observers_.insert(static_cast<T*>(observer));
		}
		else
		{
			toAdd_.insert(static_cast<T*>(observer));
		}
	}

	template <typename T>
	void inviwo::Observable<T>::removeObserverInternal(Observer* observer) {
		if (invocationCount_ == 0)
		{
			observers_.erase(static_cast<T*>(observer));
		} 
		else
		{
			toRemove_.insert(static_cast<T*>(observer));
		}
	}

	namespace util {
		class IVW_CORE_API NotificationBlocker {
		public:
			NotificationBlocker(ObservableInterface& observable);
			NotificationBlocker() = delete;
			NotificationBlocker(const NotificationBlocker&) = delete;
			NotificationBlocker(NotificationBlocker&&) = delete;
			NotificationBlocker& operator=(NotificationBlocker) = delete;
			~NotificationBlocker();
		private:
			ObservableInterface& observable_;
		};

	}
}
#endif