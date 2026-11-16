#ifndef RAYTRACER_LOG_H
#define RAYTRACER_LOG_H

#include <string>
#include <iostream>

/**
 * Provides lightweight logging utilities.
 * 
 * Exposes functions for reporting warnings and errors
 * through the standard error stream.
 */
namespace Log
{
    /**
     * Writes a warning message to the standard error stream.
     *
     * @param message Warning message to display.
     */
    inline void Warning(const std::string& message)
    {
        std::cerr << "[WARNING] " << message << '\n';
    }

    /**
     * Writes an error message to the standard error stream.
     *
     * @param message Error message to display.
     */
    inline void Error(const std::string& message)
    {
        std::cerr << "[ERROR] " << message << '\n';
    }
}

#endif // RAYTRACER_LOGGER_H