#ifndef xorshift32_h
#define xorshift32_h

#include <ap_int.h>

struct xorshift32
{
    typedef ap_uint<32> value_type;

    /* The state word must be initialized to non-zero */
    value_type state[1];

    value_type next()
    {
#pragma HLS ARRAY_PARTITION variable=state complete dim=0

        /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
        value_type x = state[0];
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        state[0] = x;
        return x;
    }
};

#endif
