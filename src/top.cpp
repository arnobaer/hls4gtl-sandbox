#include "top.h"

#include "condition.hxx"
#include "impl.hxx"

void top(const input_type& input, output_type& output)
{
    #pragma HLS INTERFACE ap_none port=input
    #pragma HLS INTERFACE ap_none port=output
    #pragma HLS INTERFACE ap_ctrl_none port=return

    #pragma HLS array_partition variable=input.objects complete dim=0
    #pragma HLS array_partition variable=output.algorithms complete dim=0

    impl::object_logic ol;
    ol.process(input);

    impl::condition_logic cl;
    cl.process(ol);

    impl::algorithm_logic al;
    al.process(cl);
    al.map(output.algorithms);
}
