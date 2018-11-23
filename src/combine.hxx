#ifndef hls4gtl_sandbox_combine_hxx
#define hls4gtl_sandbox_combine_hxx

#include <ap_int.h>
#include <cstddef>

template<size_t>
struct combine
{
};

template<>
struct combine<1>
{
    template<size_t MIN, size_t MAX>
    struct slice
    {
        template<typename T>
        static signal_type process(const T& data)
        {
#pragma HLS INTERFACE ap_none port=data
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_PARTITION variable=data dim=0

            signal_type result = false;

            for (size_t a = MIN; a <= MAX; ++a)
            {
#pragma HLS UNROLL
                result |= data[0][a];
            }

            return result;
        }
    }; // struct slice
}; // struct combine<1>

template<>
struct combine<2>
{
    template<size_t MIN, size_t MAX>
    struct slice
    {
        template<typename T>
        static signal_type process(const T& data)
        {
#pragma HLS INTERFACE ap_none port=data
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_PARTITION variable=data dim=0

            signal_type result = false;

            for (size_t a = MIN; a <= MAX; ++a)
            {
#pragma HLS UNROLL
                for (size_t b = MIN; b <= MAX; ++b)
                {
#pragma HLS UNROLL
                    if (a != b)
                    {
                        result |= data[0][a] and data[1][b];
                    }
                }
            }

            return result;
        }
    }; // struct slice
}; // struct combine<2>

template<>
struct combine<3>
{
    template<size_t MIN, size_t MAX>
    struct slice
    {
        template<typename T>
        static signal_type process(const T& data)
        {
#pragma HLS INTERFACE ap_none port=data
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_PARTITION variable=data dim=0

            signal_type result = false;

            for (size_t a = MIN; a <= MAX; ++a)
            {
#pragma HLS UNROLL
                for (size_t b = MIN; b <= MAX; ++b)
                {
#pragma HLS UNROLL
                    for (size_t c = MIN; c <= MAX; ++c)
                    {
#pragma HLS UNROLL
                        if (a != b and a != c and b != c)
                        {
                            result |= data[0][a] and data[1][b] and data[2][c];
                        }
                    }
                }
            }

            return result;
        }
    }; // struct slice
}; // struct combine<3>

template<>
struct combine<4>
{
    template<size_t MIN, size_t MAX>
    struct slice
    {
        template<typename T>
        static signal_type process(const size_t a, const size_t b, const T& data)
        {
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        #pragma HLS ARRAY_PARTITION variable=data dim=0

            signal_type result = false;

            for (size_t c = MIN; c <= MAX; ++c)
            {
#pragma HLS UNROLL
                for (size_t d = MIN; d <= MAX; ++d)
                {
#pragma HLS UNROLL
                    if (a != b and a != c and a != d and b != c and b != d and c != d)
                    {
                        result |= data[0][a] and data[1][b] and data[2][c] and data[3][d];
                    }
                }
            }

            return result;
        }

        template<typename T>
        static signal_type process(const T& data)
        {
#pragma HLS INTERFACE ap_none port=data
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_PARTITION variable=data dim=0

            signal_type result = false;

            for (size_t a = MIN; a <= MAX; ++a)
            {
#pragma HLS UNROLL
                for (size_t b = MIN; b <= MAX; ++b)
                {
#pragma HLS UNROLL
                    result |= process(a, b, data); // workaround to reduce memory load
                }
            }

            return result;
        }
    }; // struct slice
}; // struct combine<4>

#endif
