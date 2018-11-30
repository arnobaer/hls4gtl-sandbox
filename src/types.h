#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include <ap_int.h>

enum charge_type
{
    chg_ignore,
    chg_positive,
    chg_negative,
};

struct object
{
    size_t pt;
    size_t eta;
    size_t phi;
    ap_uint<2> charge;

    object()
    : pt(0), eta(0), phi(0), charge(chg_ignore)
    {
    }

    object(const size_t pt)
    : pt(pt), eta(0), phi(0), charge(chg_ignore)
    {
    }

    object(const size_t pt, const size_t eta, const size_t phi, const charge_type charge)
    : pt(pt), eta(eta), phi(phi), charge(charge)
    {
    }
};

// Store object comparator matches
typedef ap_uint<1> object_match;
typedef object_match object_match_vector[8];

// Store object charges for charge correlation conditions
typedef ap_uint<2> object_charge;
typedef object_charge object_charge_vector[8];

struct pt_comparator
{
    enum mode_type
    {
        ge,
        eq,
    };
    size_t pt;
    mode_type mode;

    pt_comparator(const size_t pt)
    : pt(pt), mode(pt_comparator::ge)
    {
    }

    pt_comparator(const size_t pt, const mode_type mode)
    : pt(pt), mode(mode)
    {
    }

    template<typename T>
    ap_uint<1> match(const T& object) const
    {
        ap_uint<1> result = false;
        switch (mode)
        {
            case ge: result = object.pt >= pt; break;
            case eq: result = object.pt == pt; break;
            default: break;
        }
        return result;
    }
};

struct eta_comparator
{
    size_t minimum;
    size_t maximum;

    eta_comparator(const size_t minimum, const size_t maximum)
    : minimum(maximum), maximum(maximum)
    {
    }

    template<typename T>
    ap_uint<1> match(const T& object) const
    {
        return object.eta >= minimum and object.eta <= maximum;
    }
};

struct phi_comparator
{
    size_t minimum;
    size_t maximum;

    phi_comparator(const size_t minimum, const size_t maximum)
    : minimum(maximum), maximum(maximum)
    {
    }

    template<typename T>
    ap_uint<1> match(const T& object) const
    {
        return object.phi >= minimum and object.phi <= maximum;
    }
};

namespace condition {

enum chgcor_mode_type
{
    ignore,
    like_sign,
    opposite_sign,
};

struct combine
{
    ap_uint<1> future_param;

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
                        if (i != j)
                        {
                            ap_uint<1> chgcor = true;
                            switch (chgcor_mode)
                            {
                                case like_sign: chgcor = (charge_1[i] == charge_2[j]); break;
                                case opposite_sign: chgcor = not (charge_1[i] == charge_2[j]); break;
                                default: chgcor = true; break;
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
                            if (i != j and i != k and j != k)
                            {
                                ap_uint<1> chgcor = true;
                                switch (chgcor_mode)
                                {
                                    case like_sign: chgcor = (charge_1[i] == charge_2[j] and charge_2[j] == charge_3[k]); break;
                                    case opposite_sign: chgcor = not (charge_1[i] == charge_2[j] and charge_2[j] == charge_3[k]); break;
                                    default: chgcor = true; break;
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
                                if (i != j and i != k and i != l and j != k and j != l and k != l)
                                {
                                    ap_uint<1> chgcor = true;
                                    switch (chgcor_mode)
                                    {
                                        case like_sign: chgcor = (charge_1[i] == charge_2[j] and charge_2[j] == charge_3[k] and charge_3[k] == charge_4[l]); break;
                                        case opposite_sign: chgcor = not (charge_1[i] == charge_2[j] and charge_2[j] == charge_3[k] and charge_3[k] == charge_4[l]); break;
                                        default: chgcor = true; break;
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

struct input_type
{
    typedef size_t size_type;

    static const size_type size = 8;

    object objects[5][size];
};

struct output_type
{
    typedef size_t size_type;

    static const size_type size = 8;

    typedef ap_uint<1> value_type;
    typedef value_type algorithms_type[size];

    algorithms_type algorithms;
};

#endif
