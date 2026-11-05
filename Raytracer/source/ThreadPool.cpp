#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount)
{
	try
	{
		// Create worker threads
		for (size_t idx = 0; idx < threadCount; ++idx)
		{
			threads.emplace_back(&ThreadPool::WorkerLoop, this);
		}
	}
	catch (...)
	{
		Stop();
		throw;
	}
}

void ThreadPool::WorkerLoop()
{
	while (true)
	{
		std::function<void()> task;

		// Unlock the queue before executing the task so that other threads can perform enqueue tasks
		{
			// Locking queue so data can be shared safely
			std::unique_lock<std::mutex> lock(queueMutex);

			// Waiting until there is a task to execute or the pool is stopped
			condition.wait(lock, [this]
				{
					return !tasks.empty() || stop;
				});

			// Exit the thread in case the pool is stopped and there are no tasks
			if (stop && tasks.empty())
			{
				return;
			}

			// Get the next task from the queue
			task = std::move(tasks.front());
			tasks.pop();
		}

		task();
	}
}

ThreadPool::~ThreadPool()
{
	Stop();
}

void ThreadPool::Stop()
{
	{
		// Lock the queue to update the stop flag safely
		std::lock_guard<std::mutex> lock(queueMutex);
		stop = true;
	}
	// Notify all threads
	condition.notify_all();

	// Joining all worker threads to ensure they have completed their tasks
	for (std::thread& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}