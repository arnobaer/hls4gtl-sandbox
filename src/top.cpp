#include "top.h"
#include "combine.hxx"

void top(const setup_type& setup, const input_type& input, output_type& output)
{
    #pragma HLS INTERFACE ap_none port=setup
    #pragma HLS INTERFACE ap_none port=input
    #pragma HLS INTERFACE ap_none port=output
    #pragma HLS INTERFACE ap_ctrl_none port=return

    #pragma HLS ARRAY_PARTITION variable=input.data dim=0

    switch (setup.dim)
    {
        case 1: output.result = combine<1>::process(setup, input.data); break;
        case 2: output.result = combine<2>::process(setup, input.data); break;
        case 3: output.result = combine<3>::process(setup, input.data); break;
        case 4: output.result = combine<4>::process(setup, input.data); break;
        default: output.result = false; break;
    }
}
