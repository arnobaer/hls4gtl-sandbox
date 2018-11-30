#ifndef hls4gtl_sandbox_utils_hxx
#define hls4gtl_sandbox_utils_hxx

#include <ap_int.h>

// test for all equal

template<typename T>
inline ap_uint<1> all_equal(const T& a, const T& b)
{
    return a == b;
}

template<typename T>
inline ap_uint<1> all_equal(const T& a, const T& b, const T& c)
{
    return a == b and b == c;
}

template<typename T>
inline ap_uint<1> all_equal(const T& a, const T& b, const T& c, const T& d)
{
    return a == b and b == c and c == d;
}

// test for all unique

template<typename T>
inline ap_uint<1> all_unique(const T& a, const T& b)
{
    return a != b;
}

template<typename T>
inline ap_uint<1> all_unique(const T& a, const T& b, const T& c)
{
    return a != b and a != c and b != c;
}

template<typename T>
inline ap_uint<1> all_unique(const T& a, const T& b, const T& c, const T& d)
{
    return a != b and a != c and a != d and b != c and b != d and c != d;
}

#endif
