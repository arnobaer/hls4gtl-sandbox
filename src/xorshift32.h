#ifndef xorshift32_h
#define xorshift32_h

#include <ap_int.h>

struct xorshift32
{
    /* The state word must be initialized to non-zero */
    ap_uint<32> state[1];

    ap_uint<32> next()
    {
        /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
        ap_uint<32> x = state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        state = x;
        return x;
    }
};

#endif
