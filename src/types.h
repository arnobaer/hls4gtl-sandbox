#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include <ap_int.h>
#include <cstddef>

typedef ap_uint<1> signal_type;

struct input_type
{
    typedef ap_uint<1> value_type;
    typedef size_t size_type;

    static const size_type dim = 4;
    static const size_type size = 12;

    value_type data[dim][size];
};

struct output_type
{
    typedef ap_uint<1> value_type;
    typedef size_t size_type;

    static const size_type size = 4;

    value_type result[size];
};

#endif
