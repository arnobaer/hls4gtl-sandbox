#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include <ap_int.h>

struct object
{
    size_t pt;
    size_t eta;
    size_t phi;

    object()
    : pt(0), eta(0), phi(0)
    {
    }

    object(const size_t pt)
    : pt(pt), eta(0), phi(0)
    {
    }

    object(const size_t pt, const size_t eta, const size_t phi)
    : pt(pt), eta(eta), phi(phi)
    {
    }
};

typedef ap_uint<1> object_match;
typedef object_match object_match_vector[8];

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

struct condition
{
    enum chgcorr_mode_type
    {
        ignore,
        positive,
        negative,
    };

    size_t slice_min;
    size_t slice_max;
    chgcorr_mode_type  chgcorr_mode;

    template<typename T, size_t N>
    ap_uint<1> match(const T (&vector_1)[N]) const
    {
        #pragma HLS array_partition variable=vector_1 complete dim=0

        ap_uint<1> result = false;
        for (size_t i = slice_min; i < slice_max; ++i)
        {
            #pragma HLS UNROLL
            result |= vector_1[i];
        }
        return result;
    }

    template<typename T, size_t N, typename C, size_t X>
    ap_uint<1> match(const T (&vector_1)[N], const T (&vector_2)[N], const C (&chgcor)[X][X]) const
    {
        #pragma HLS array_partition variable=vector_1 complete dim=0
        #pragma HLS array_partition variable=vector_2 complete dim=0
        #pragma HLS array_partition variable=chgcor complete dim=0

        ap_uint<1> result = false;
        for (size_t i = slice_min; i < slice_max; ++i)
        {
            #pragma HLS UNROLL
            for (size_t j = slice_min; j < slice_max; ++j)
            {
                #pragma HLS UNROLL
                if (i != j)
                {
                    ap_uint<1> chgcor_result;
                    switch (chgcorr_mode)
                    {
                        case positive: chgcor_result = (chgcor[i][j] == true); break;
                        case negative: chgcor_result = (chgcor[i][j] == false); break;
                        default: chgcor_result = true; break;
                    }
                    result |= vector_1[i] and vector_2[j] and chgcor_result;
                }
            }
        }
        return result;
    }

    template<typename T, size_t N, typename C, size_t X>
    ap_uint<1> match(const T (&vector_1)[N], const T (&vector_2)[N], const T (&vector_3)[N], const C (&chgcor)[X][X][X]) const
    {
        #pragma HLS array_partition variable=vector_1 complete dim=0
        #pragma HLS array_partition variable=vector_2 complete dim=0
        #pragma HLS array_partition variable=vector_3 complete dim=0
        #pragma HLS array_partition variable=chgcor complete dim=0

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
                        ap_uint<1> chgcor_result;
                        switch (chgcorr_mode)
                        {
                            case positive: chgcor_result = (chgcor[i][j][k] == true); break;
                            case negative: chgcor_result = (chgcor[i][j][k] == false); break;
                            default: chgcor_result = true; break;
                        }
                        result |= vector_1[i] and vector_2[j] and vector_3[k] and chgcor_result;
                    }
                }
            }
        }
        return result;
    }

    template<typename T, size_t N, typename C, size_t X>
    ap_uint<1> match(const T (&vector_1)[N], const T (&vector_2)[N], const T (&vector_3)[N], const T (&vector_4)[N], const C (&chgcor)[X][X][X][X]) const
    {
        #pragma HLS array_partition variable=vector_1 complete dim=0
        #pragma HLS array_partition variable=vector_2 complete dim=0
        #pragma HLS array_partition variable=vector_3 complete dim=0
        #pragma HLS array_partition variable=vector_4 complete dim=0
        #pragma HLS array_partition variable=chgcor complete dim=0

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
                            ap_uint<1> chgcor_result;
                            switch (chgcorr_mode)
                            {
                                case positive: chgcor_result = (chgcor[i][j][k][l] == true); break;
                                case negative: chgcor_result = (chgcor[i][j][k][l] == false); break;
                                default: chgcor_result = true; break;
                            }
                            result |= vector_1[i] and vector_2[j] and vector_3[k] and vector_4[l] and chgcor_result;
                        }
                    }
                }
            }
        }
        return result;
    }
};

struct input_type
{
    static const size_t size = 8;

    object objects[5][size];

    ap_uint<1> chgcor_double[size][size];
    ap_uint<1> chgcor_triple[size][size][size];
    ap_uint<1> chgcor_quad[size][size][size][size];
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
