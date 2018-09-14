#include "threadpool.h"
#include "raiiutils.h"
#include "stdextensions.h"

namespace inviwo {

	ThreadPool::ThreadPool(size_t threads, 
						   std::function<void()> onThreadStart,
						   std::function<void()> onThreadStop)
		: onThreadStart_{std::move(onThreadStart)}
		, onThreadStop_{std::move(onThreadStop)}
	{
		while (workers.size() < threads)
		{
			workers.push_back(util::make_unique<Worker>(*this));
		}
	}
	size_t ThreadPool::trySetSize(size_t size) {
		while (workers.size() < size) {
			workers.push_back(util::make_unique<Worker>(*this));
		}

		if (workers.size() > size) {
			auto active = workers.size();
			for (auto& worker : workers) {
				auto exprected = State::Free;
				if (worker->state.compare_exchange_strong(exprected, State::Stop)) {
					--active;
				}
				else if (exprected == State::Stop || exprected == State::Done) {
					--active;
				}
				if (active <= size) break;
			}

			condition.notify_all();

			util::erase_remove_if(workers, [this](std::unique_ptr<Worker>& worker) {
				return worker->state == State::Done;
			});
		}
		return workers.size();
	}

	size_t ThreadPool::getSize() const { return workers.size(); }

	ThreadPool::~ThreadPool() {
		for (auto& worker : workers) worker->state = State::Abort;
		condition.notify_all();
		workers.clear(); // this will join all threads.
	}

	ThreadPool::Worker::~Worker() { thread.join(); }
	ThreadPool::Worker::Worker(ThreadPool& pool)
		: state{ State::Free }
		, thread{ [this, &pool]() {
			pool.onThreadStart_();
			util::OnScopeExit cleanup{ [&pool]() { pool.onThreadStop_(); } };

			std::function<void()> task;
			for (;;) {
				state = State::Free;
				{
					std::unique_lock<std::mutex> lock(pool.queue_mutex);
					pool.condition.wait(lock, [this, &pool] {
						return state == State::Abort || state == State::Stop || !pool.tasks.empty();
					});
					if (state == State::Abort || (state == State::Stop && pool.tasks.empty())) break;
					task = std::move(pool.tasks.front());
					pool.tasks.pop();
				}
				state = State::Working;
				task();
			}
			state = State::Done;
}}{}

}