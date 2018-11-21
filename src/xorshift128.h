#ifndef xorshift128_h
#define xorshift128_h

#include <ap_int.h>

struct xorshift128
{
    typedef ap_uint<32> value_type;

    /* The state array must be initialized to not be all zero */
    value_type state[4];

    value_type next()
    {
#pragma HLS ARRAY_PARTITION variable=state complete dim=0

        /* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
        value_type s = 0;
        value_type t = state[3];
        t ^= t << 11;
        t ^= t >> 8;
        state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
        t ^= s;
        t ^= s >> 19;
        state[0] = t;
        return t;
    }
};

#endif
