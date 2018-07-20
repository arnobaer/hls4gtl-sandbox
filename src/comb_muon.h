#ifndef hls4gtl_comb_muon_h
#define hls4gtl_comb_muon_h

#include "types.h"

template<typename T, size_t N_REQ>
bool_t comb_muon(const T objects, const typename T::req_t reqs[N_REQ])
{
#pragma HLS ARRAY_PARTITION variable=objects complete dim=0
#pragma HLS ARRAY_PARTITION variable=reqs complete dim=0

	size_t count = 0;
	ap_array<bool_t, objects.size()> vetos = {};
#pragma HLS ARRAY_PARTITION variable=vetos complete dim=0

	for (size_t req_it = 0; req_it < N_REQ; ++req_it)
	{
#pragma HLS UNROLL
		for (size_t obj_it = 0; obj_it < objects.size(); ++obj_it)
		{
#pragma HLS UNROLL
			if (vetos[obj_it] == false)
			{
				if (objects[obj_it].et >= reqs[req_it].et_threshold)
				{
					++count;
					break; // Well.. will that work? No of course not!
				}
				vetos[obj_it] = true;
			}
		}
	}

	return count >= N_REQ;
}

#endif
