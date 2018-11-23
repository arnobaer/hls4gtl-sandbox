#include "top.h"
#include "combine.hxx"

void top(const input_type& input, output_type& output)
{
#pragma HLS INTERFACE ap_none port=input
#pragma HLS INTERFACE ap_none port=output
#pragma HLS INTERFACE ap_ctrl_none port=return

    output.result[0] = combine<1>::slice<0, 11>::process(input.data);
    output.result[1] = combine<2>::slice<0, 11>::process(input.data);
    output.result[2] = combine<3>::slice<0, 11>::process(input.data);
    output.result[3] = combine<4>::slice<0, 11>::process(input.data);
}
