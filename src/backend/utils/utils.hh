#pragma once

template<typename T>
inline T sqr(T x) { return x * x; }

template<typename T>
inline T discr(T a, T b, T c) { return sqr(b) - (4 * a * c); }

template<typename T>
inline T abs(T x) { return x < 0 ? -x : x; }
