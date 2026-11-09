template<typename F>
auto ThreadPool::Enqueue(F&& function)
{
	using ReturnType = decltype(function());

	auto task = std::make_shared<std::packaged_task<ReturnType()>>(
		std::forward<F>(function)
	);

#ifdef result
#error "result already macro"
#endif

	std::future<ReturnType> result = task->get_future();

	std::unique_lock<std::mutex> lock(queueMutex);

	if (stop)
	{
		throw std::runtime_error("ThreadPool stopped");
	}

	tasks.emplace([task]()
		{
			(*task)();
		});


	condition.notify_one();

	return result;

}