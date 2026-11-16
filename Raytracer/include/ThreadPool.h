#ifndef RAYTRACER_THREAD_POOL_H
#define RAYTRACER_THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <future>
#include <memory>
#include <utility>
#include <stdexcept>

/**
 * Manages a pool of worker threads for asynchronous task execution.
 *
 * Maintains a shared task queue and distributes submitted tasks
 * among available worker threads.
 * 
 * Synchronizes task access and thread execution using mutexes
 * and condition variables.
 */
class ThreadPool
{
public:
	/**
	 * Creates a thread pool with the specified number of workers.
	 *
	 * Starts the worker threads and prepares the shared task queue
	 * for asynchronous task execution.
	 *
	 * @param threadCount Number of worker threads to create.
	 */
	ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
	/**
	 * Stops the thread pool and joins all worker threads.
	 *
	 * Ensures that worker threads terminate before the pool is destroyed.
	 */
	~ThreadPool();

	/**
	 * Submits a task for asynchronous execution.
	 *
	 * Adds the task to the shared queue and returns a future
	 * containing its eventual result.
	 *
	 * @tparam F Type of the submitted callable.
	 * @param task Callable object to execute.
	 * @return Future associated with the task result.
	 */
	template<typename F>
	auto Enqueue(F&& task);

private:
	/**
	 * Executes the worker thread task-processing loop.
	 *
	 * Waits for tasks to become available, retrieves them from
	 * the shared queue and executes them until the pool is stopped.
	 */
	void WorkerLoop();
	/**
	 * Signals worker threads to stop and waits for their termination.
	 * Updates the pool state, wakes waiting workers and joins
	 * all joinable threads.
	 */
	void Stop();

	// Worker threads owned by this pool
	std::vector<std::thread> threads;

	// Pending tasks waiting to be executed by a worker
	std::queue<std::function<void()>> tasks;

	// Protects access to the task queue and pool state
	std::mutex queueMutex;
	// Wakes workers when tasks are queued or shutdown is requested
	std::condition_variable condition;

	// Indicates that the pool is shutting down and workers must exit
	bool stop = false;
};

#include "ThreadPool.inl"

#endif // RAYTRACER_THREAD_POOL_H