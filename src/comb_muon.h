#ifndef comb_muon_h
#define comb_muon_h

#include "types.h"

template<size_t N_REQ>
ap_uint<1> comb_muon(const muon_t muons[N_MUONS], const muon_req_t reqs[N_REQ])
{
#pragma HLS ARRAY_PARTITION variable=muons complete dim=0
#pragma HLS ARRAY_PARTITION variable=reqs complete dim=0

	size_t count = 0;
	bool_t vetos[N_MUONS] = {};
#pragma HLS ARRAY_PARTITION variable=vetos complete dim=0

	for (size_t req_it = 0; req_it < N_REQ; ++req_it)
	{
#pragma HLS UNROLL
		for (size_t obj_it = 0; obj_it < N_MUONS; ++obj_it)
		{
#pragma HLS UNROLL
			if (vetos[obj_it] == false)
			{
				if (muons[obj_it].et >= reqs[req_it].et_threshold)
				{
					++count;
					break; // Well.. will that work?
				}
				vetos[obj_it] = true;
			}
		}
	}

	return count >= N_REQ;
}

#endif
