#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include <ap_int.h>
#include <cstddef>

typedef ap_uint<1> signal_type;

template<typename T>
struct slice_type
{
    typedef T value_type;

    value_type minimum;
    value_type maximum;
};

struct setup_type
{
    typedef size_t size_type;

    size_type dim;
    slice_type<size_type> slice;
};

struct input_type
{
    typedef ap_uint<1> value_type;
    typedef size_t size_type;

    static const size_type dim = 4;
    static const size_type size = 12;

    typedef value_type object_vector[size];

    object_vector data[dim];
};

struct output_type
{
    typedef ap_uint<1> value_type;

    value_type result;
};

#endif
