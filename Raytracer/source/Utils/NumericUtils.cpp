#include "Utils/NumericUtils.h"

int NumericUtils::ToInt(size_t value)
{
    if (value > static_cast<size_t>(std::numeric_limits<int>::max()))
        throw std::overflow_error("Value exceeds int range");

    return static_cast<int>(value);
}