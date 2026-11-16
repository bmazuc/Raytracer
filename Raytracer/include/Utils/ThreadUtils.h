#ifndef RAYTRACER_THREAD_UTILS_H
#define RAYTRACER_THREAD_UTILS_H

#include <thread>

namespace ThreadUtils
{
	/**
	 * Returns the hardware concurrency minus 1 for the main thread
	 */
	inline unsigned int GetMaxThreadAvailable()
	{
		return std::max(1u, std::thread::hardware_concurrency() - 1u);
	}
}

#endif // RAYTRACER_THREAD_UTILS_H