#pragma once

template<typename T>
inline T abs(T value)
{
    if (value < 0)
        return -value;
    return value;
}