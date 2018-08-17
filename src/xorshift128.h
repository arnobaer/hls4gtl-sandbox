#ifndef xorshift128_h
#define xorshift128_h

#include <ap_int.h>

struct xorshift128
{
    /* The state array must be initialized to not be all zero */
	ap_uint<32> state[4];

	ap_uint<32> next()
	{
		/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
		ap_uint<32> s, t = state[3];
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
