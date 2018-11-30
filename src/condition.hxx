#ifndef hls4gtl_sandbox_condition_hxx
#define hls4gtl_sandbox_condition_hxx

#include <ap_int.h>
#include <cstddef>

namespace condition {

enum chgcor_mode_type
{
    ignore,
    like_sign,
    opposite_sign,
};

struct combine
{
    typedef ap_uint<1> return_type;
    typedef ap_uint<1> future_param_type;

    future_param_type future_param;

    template<size_t slice_min, size_t slice_max>
    struct slice
    {
        template<chgcor_mode_type chgcor_mode>
        struct chgcor
        {
            ap_uint<1> future_param;

            template<typename T, size_t N>
            ap_uint<1> match(const T (&vector_1)[N]) const
            {
                #pragma HLS INTERFACE ap_none port=vector_1
                #pragma HLS INTERFACE ap_ctrl_none port=return

                #pragma HLS array_partition variable=vector_1 complete dim=0

                ap_uint<1> result = false;
                for (size_t i = slice_min; i < slice_max; ++i)
                {
                    #pragma HLS UNROLL
                    result |= vector_1[i];
                }
                return result;
            }

            template<typename T1, typename T2, size_t N>
            ap_uint<1> match(const T1 (&vector_1)[N], const T1 (&vector_2)[N],
                             const T2 (&charge_1)[N], const T2 (&charge_2)[N]) const
            {
                #pragma HLS INTERFACE ap_none port=vector_1
                #pragma HLS INTERFACE ap_none port=vector_2
                #pragma HLS INTERFACE ap_none port=charge_1
                #pragma HLS INTERFACE ap_none port=charge_2
                #pragma HLS INTERFACE ap_ctrl_none port=return

                #pragma HLS array_partition variable=vector_1 complete dim=0
                #pragma HLS array_partition variable=vector_2 complete dim=0
                #pragma HLS array_partition variable=charge_1 complete dim=0
                #pragma HLS array_partition variable=charge_2 complete dim=0

                ap_uint<1> result = false;
                for (size_t i = slice_min; i < slice_max; ++i)
                {
                    #pragma HLS UNROLL
                    for (size_t j = slice_min; j < slice_max; ++j)
                    {
                        #pragma HLS UNROLL
                        if (all_unique(i, j))
                        {
                            ap_uint<1> chgcor;
                            switch (chgcor_mode)
                            {
                                case like_sign:
                                    chgcor = all_equal(charge_1[i], charge_2[j]);
                                    break;
                                case opposite_sign:
                                    chgcor = not all_equal(charge_1[i], charge_2[j]);
                                    break;
                                default:
                                    chgcor = true;
                                    break;
                            }
                            result |= vector_1[i] and vector_2[j] and chgcor;
                        }
                    }
                }
                return result;
            }

            template<typename T1, typename T2, size_t N>
            ap_uint<1> match(const T1 (&vector_1)[N], const T1 (&vector_2)[N], const T1 (&vector_3)[N],
                             const T2 (&charge_1)[N], const T2 (&charge_2)[N], const T2 (&charge_3)[N]) const
            {
                #pragma HLS INTERFACE ap_none port=vector_1
                #pragma HLS INTERFACE ap_none port=vector_2
                #pragma HLS INTERFACE ap_none port=vector_3
                #pragma HLS INTERFACE ap_none port=charge_1
                #pragma HLS INTERFACE ap_none port=charge_2
                #pragma HLS INTERFACE ap_none port=charge_3
                #pragma HLS INTERFACE ap_ctrl_none port=return

                #pragma HLS array_partition variable=vector_1 complete dim=0
                #pragma HLS array_partition variable=vector_2 complete dim=0
                #pragma HLS array_partition variable=vector_3 complete dim=0
                #pragma HLS array_partition variable=charge_1 complete dim=0
                #pragma HLS array_partition variable=charge_2 complete dim=0
                #pragma HLS array_partition variable=charge_3 complete dim=0

                ap_uint<1> result = false;
                for (size_t i = slice_min; i < slice_max; ++i)
                {
                    #pragma HLS UNROLL
                    for (size_t j = slice_min; j < slice_max; ++j)
                    {
                        #pragma HLS UNROLL
                        for (size_t k = slice_min; k < slice_max; ++k)
                        {
                            #pragma HLS UNROLL
                            if (all_unique(i, j, k))
                            {
                                ap_uint<1> chgcor;
                                switch (chgcor_mode)
                                {
                                    case like_sign:
                                        chgcor = all_equal(charge_1[i], charge_2[j], charge_3[k]);
                                        break;
                                    case opposite_sign:
                                        chgcor = not all_equal(charge_1[i], charge_2[j], charge_3[k]);
                                        break;
                                    default:
                                        chgcor = true;
                                        break;
                                }
                                result |= vector_1[i] and vector_2[j] and vector_3[k] and chgcor;
                            }
                        }
                    }
                }
                return result;
            }

            template<typename T1, typename T2, size_t N>
            ap_uint<1> match(const T1 (&vector_1)[N], const T1 (&vector_2)[N], const T1 (&vector_3)[N], const T1 (&vector_4)[N],
                             const T2 (&charge_1)[N], const T2 (&charge_2)[N], const T2 (&charge_3)[N], const T2 (&charge_4)[N]) const
            {
                #pragma HLS INTERFACE ap_none port=vector_1
                #pragma HLS INTERFACE ap_none port=vector_2
                #pragma HLS INTERFACE ap_none port=vector_3
                #pragma HLS INTERFACE ap_none port=vector_4
                #pragma HLS INTERFACE ap_none port=charge_1
                #pragma HLS INTERFACE ap_none port=charge_2
                #pragma HLS INTERFACE ap_none port=charge_3
                #pragma HLS INTERFACE ap_none port=charge_4
                #pragma HLS INTERFACE ap_ctrl_none port=return

                #pragma HLS array_partition variable=vector_1 complete dim=0
                #pragma HLS array_partition variable=vector_2 complete dim=0
                #pragma HLS array_partition variable=vector_3 complete dim=0
                #pragma HLS array_partition variable=vector_4 complete dim=0
                #pragma HLS array_partition variable=charge_1 complete dim=0
                #pragma HLS array_partition variable=charge_2 complete dim=0
                #pragma HLS array_partition variable=charge_3 complete dim=0
                #pragma HLS array_partition variable=charge_4 complete dim=0

                ap_uint<1> result = false;
                for (size_t i = slice_min; i < slice_max; ++i)
                {
                    #pragma HLS UNROLL
                    for (size_t j = slice_min; j < slice_max; ++j)
                    {
                        #pragma HLS UNROLL
                        for (size_t k = slice_min; k < slice_max; ++k)
                        {
                            #pragma HLS UNROLL
                            for (size_t l = slice_min; l < slice_max; ++l)
                            {
                                #pragma HLS UNROLL
                                if (all_unique(i, j, k, l))
                                {
                                    ap_uint<1> chgcor;
                                    switch (chgcor_mode)
                                    {
                                        case like_sign:
                                            chgcor = all_equal(charge_1[i], charge_2[j], charge_3[k], charge_4[l]);
                                            break;
                                        case opposite_sign:
                                            chgcor = not all_equal(charge_1[i], charge_2[j], charge_3[k], charge_4[l]);
                                            break;
                                        default:
                                            chgcor = true;
                                            break;
                                    }
                                    result |= vector_1[i] and vector_2[j] and vector_3[k] and vector_4[l] and chgcor;
                                }
                            }
                        }
                    }
                }
                return result;
            }
        }; // struct chgcor
    }; // struct slice
};

} // namespace condition

#endif
