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

class ThreadPool
{
public:
	ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
	~ThreadPool();

	template<typename F>
	auto Enqueue(F&& task);

private:
	void WorkerLoop();
	void Stop();

	// Vector to store worker threads
	std::vector<std::thread> threads;

	std::queue<std::function<void()>> tasks;

	// Mutex to synchronize access to shared data
	std::mutex queueMutex;
	// Condition variable to signal changes in the state of the tasks queue
	std::condition_variable condition;

	// Flag to indicate whether the thread pool should stop or not
	bool stop = false;
};

#include "ThreadPool.inl"

#endif // RAYTRACER_THREAD_POOL_H