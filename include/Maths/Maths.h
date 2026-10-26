#ifndef __MATHS_H_INCLUDED__
#define __MATHS_H_INCLUDED__

#include <limits>

namespace maths
{
    // Constants

    const float infinity = std::numeric_limits<float>::infinity();
    const float pi = 3.1415926535897932385f;

    // Utility Functions

    inline float degreesToRadians(float degrees)
    {
        return degrees * pi / 180.f;
    }
}

#endif // __MATHS_H_INCLUDED__