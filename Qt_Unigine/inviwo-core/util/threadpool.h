/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: threadpool
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 14:13:46
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_THREADPOOL_H
#define IVW_THREADPOOL_H

#include "../inviwocoredefine.h"

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>

namespace inviwo {

	class IVW_CORE_API ThreadPool {
	public:
		ThreadPool(size_t threads, std::function<void()> onThreadStart = []() {},
			std::function<void()> onThreadStop = []() {});
		~ThreadPool();
		template <class F, class... Args>
		auto enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
		size_t trySetSize(size_t size);
		size_t getSize() const;

	private:
		enum class State {
			Free,     //< Worker is waiting for tasks.
			Working,  //< Worker is running a task.
			Stop,     //< Stop after all tasks are done.
			Abort,    //< Stop as soon as possible, no matter if there are more tasks.
			Done      //< Worker is waiting to be joined.
		};

		struct Worker {
			Worker(ThreadPool& pool);
			Worker(const Worker&) = delete;
			Worker(Worker&& rhs) = delete;
			Worker& operator=(const Worker&) = delete;
			Worker& operator=(Worker&& rhs) = delete;
			~Worker();

			std::atomic<State> state; //< State of the worker
			std::thread thread;
		};

		// need to keep track of threads so we can join them
		std::vector<std::unique_ptr<Worker>> workers;

		// the task queue
		std::queue<std::function<void()>> tasks;

		// synchronization
		std::mutex queue_mutex;
		std::condition_variable condition;

		// Thread start end exit actions
		std::function<void()> onThreadStart_;
		std::function<void()> onThreadStop_;
	};
}

#endif
