#include "gtl.h"
#include "comb_muon.h"

#include <iostream>

void gtl(const input_t& input, output_t& output)
{
#pragma HLS ARRAY_PARTITION variable=input.muons complete dim=1
#pragma HLS ARRAY_PARTITION variable=output.algorithms complete dim=1

	// Requirements
	const muon_t::cuts_t muon_cuts_01 = {0x42, 0x1, 0x0};
	const muon_t::cuts_t muon_cuts_02 = {0x46, 0x0, 0x1};
	const muon_t::cuts_t muon_cuts_03 = {0x14, 0x0, 0x0};
	const muon_t::cuts_t muon_cuts_04 = {0x14, 0x0, 0x0};
	const muon_t::cuts_t muon_cuts_05 = {0x8, 0x0, 0x0};
	const muon_t::cuts_t muon_cuts_06 = {0x2, 0x0, 0x0};
/*
	// Conditions
	const ap_uint<1> cond_single_muon_01 = comb_muon<1>(input.muons, (muon_cuts_t[]){muon_cuts_01});
	const ap_uint<1> cond_double_muon_02 = comb_muon<2>(input.muons, (muon_cuts_t[]){muon_cuts_02, muon_cuts_01});
	const ap_uint<1> cond_single_muon_03 = comb_muon<1>(input.muons, (muon_cuts_t[]){muon_cuts_03});
	const ap_uint<1> cond_single_muon_04 = comb_muon<1>(input.muons, (muon_cuts_t[]){muon_cuts_04});
	const ap_uint<1> cond_single_muon_05 = comb_muon<1>(input.muons, (muon_cuts_t[]){muon_cuts_05});
	const ap_uint<1> cond_single_muon_06 = comb_muon<1>(input.muons, (muon_cuts_t[]){muon_cuts_06});
	const ap_uint<1> cond_quad_muon_07 = comb_muon<4>(input.muons, (muon_cuts_t[]){muon_cuts_05, muon_cuts_05, muon_cuts_05, muon_cuts_05});

	// Algorithms
	output.algorithms[0] = cond_single_muon_03;
	output.algorithms[1] = cond_single_muon_04;
	output.algorithms[2] = cond_single_muon_05;
	output.algorithms[3] = cond_single_muon_06;
	output.algorithms[4] = cond_single_muon_01 and cond_double_muon_02;
	output.algorithms[5] = cond_quad_muon_07;
*/
	// Calculate final OR
	for (size_t i = 0; i < output.algorithms.size(); ++i)
	{
#pragma HLS UNROLL
		output.final |= output.algorithms.at(i);
	}
}
