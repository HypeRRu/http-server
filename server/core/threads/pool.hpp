#ifndef CORE_THREADS_POOL_HPP
#define CORE_THREADS_POOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <deque>
#include <vector>
#include <atomic>

namespace core
{
	namespace threads
	{
		class Pool
		{
		public:
			Pool(std::size_t count = 0):
				pool_work_ended_{false}
			{
				start_threads(count);
			}

			~Pool()
			{
				shutdown();
			}

			void shutdown()
			{
				/* may cause std::future_error: Broken promise */
				pool_work_ended_ = true;
				cond_.notify_all();
				std::unique_lock<std::mutex> lock(mtx_);
				tasks_.clear();
				finished_.clear();
			}

			template <class F, class R = typename std::result_of<F&()>::type>
			std::future<R> add_task(F&& f)
			{
				if (pool_work_ended_)
					return {};
				/* wrap the function object into a packaged task */
				std::packaged_task<R()> task(std::forward<F>(f));
				std::future<R> retval = task.get_future();
				/* store the task<R()> as a task<void()> */
				{
					std::unique_lock<std::mutex> lock(mtx_);
					tasks_.emplace_back(std::move(task));
				}
				/* wake a thread to work on the task */
				cond_.notify_one();
				/* return the future result */
				return retval;
			}

			void start_threads(std::size_t count = 1)
			{
				for (std::size_t i = 0; i < count; ++i)
				{
					/* each thread is a std::async running */
					finished_.push_back(
						std::async(
							std::launch::async, 
							[this] ()
							{
								thread_task();
							}
						)
					);
				}
			}
		protected:
			void thread_task()
			{
				while (!pool_work_ended_)
				{
					/* pop a task off the queue */
					std::packaged_task<void()> task;
					{
						std::unique_lock<std::mutex> lock(mtx_);
						if (tasks_.empty())
						{
							cond_.wait(
								lock,
								[&] ()
								{
									return (
										!tasks_.empty() ||
										pool_work_ended_
									);
								}
							);
							/* check for abortion */
							if (pool_work_ended_)
								return;
						}
						task = std::move(tasks_.front());
						tasks_.pop_front();
					}
					/* run the task */
					task();
				}
			}

			std::mutex mtx_;
			std::condition_variable cond_;
			/* packaged_task<void> can store a packaged_task<R> */
			std::deque<std::packaged_task<void()>> tasks_;
			/* running threads */
			std::vector<std::future<void>> finished_;
			std::atomic_bool pool_work_ended_;
		};
	};
};

#endif
