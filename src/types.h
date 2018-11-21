#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include <ap_int.h>
#include <cstddef>

struct input_type
{
};

struct output_type
{
  typedef ap_uint<32> value_type;
  typedef size_t size_type;

  static const size_type size = 8;

  value_type data32[size];
  value_type data128[size];
};

#endif
