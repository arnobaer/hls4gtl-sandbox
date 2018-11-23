#ifndef hls4gtl_sandbox_combine_hxx
#define hls4gtl_sandbox_combine_hxx

#include "types.h"

#include <ap_int.h>
#include <cstddef>

template<size_t>
struct combine
{
};

template<>
struct combine<1>
{
    typedef size_t size_type;

    static const size_type minimum = 0;
    static const size_type maximum = 12;

    template<typename T1, typename T2>
    static signal_type process_slice(const T1& setup, const T2& data, const size_type a)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        #pragma HLS ARRAY_PARTITION variable=data dim=0

        if (a >= setup.slice.minimum and a <= setup.slice.maximum)
        {
            return data[0][a];
        }
        return false;
    }

    template<typename T1, typename T2>
    static signal_type process(const T1& setup, const T2& data)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        signal_type result = false;

        for (size_type a = minimum; a < maximum; ++a)
        {
            #pragma HLS UNROLL
            result |= process_slice(setup, data, a);
        }

        return result;
    }
}; // struct combine<1>

template<>
struct combine<2>
{
    typedef size_t size_type;

    static const size_type minimum = 0;
    static const size_type maximum = 12;

    template<typename T1, typename T2>
    static signal_type process_slice(const T1& setup, const T2& data, const size_type a, const size_type b)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        #pragma HLS ARRAY_PARTITION variable=data dim=0

        signal_type result = false;

        if (a != b)
        {
            if (a >= setup.slice.minimum and a <= setup.slice.maximum)
            {
                if (b >= setup.slice.minimum and b <= setup.slice.maximum)
                {
                    result = data[0][a] and data[1][b];
                }
            }
        }
        return result;
    }

    template<typename T1, typename T2>
    static signal_type process(const T1& setup, const T2& data)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        signal_type result = false;

        for (size_type a = minimum; a < maximum; ++a)
        {
            #pragma HLS UNROLL
            for (size_type b = minimum; b < maximum; ++b)
            {
                #pragma HLS UNROLL
                result |= process_slice(setup, data, a, b);
            }
        }

        return result;
    }
}; // struct combine<2>

template<>
struct combine<3>
{
    typedef size_t size_type;

    static const size_type minimum = 0;
    static const size_type maximum = 12;

    template<typename T1, typename T2>
    static signal_type process_slice(const T1& setup, const T2& data, const size_type a, const size_type b, const size_type c)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        #pragma HLS ARRAY_PARTITION variable=data dim=0

        signal_type result = false;

        if (a != b and a != c and b != c)
        {
            if (a >= setup.slice.minimum and a <= setup.slice.maximum)
            {
                if (b >= setup.slice.minimum and b <= setup.slice.maximum)
                {
                    if (c >= setup.slice.minimum and c <= setup.slice.maximum)
                    {
                        result = data[0][a] and data[1][b] and data[2][c];
                    }
                }
            }
        }
        return result;
    }

    template<typename T1, typename T2>
    static signal_type process(const T1& setup, const T2& data)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        signal_type result = false;

        for (size_type a = minimum; a < maximum; ++a)
        {
            #pragma HLS UNROLL
            for (size_type b = minimum; b < maximum; ++b)
            {
                #pragma HLS UNROLL
                for (size_type c = minimum; c < maximum; ++c)
                {
                    #pragma HLS UNROLL
                    result |= process_slice(setup, data, a, b, c);
                }
            }
        }

        return result;
    }
}; // struct combine<3>

template<>
struct combine<4>
{
    typedef size_t size_type;

    static const size_type minimum = 0;
    static const size_type maximum = 12;

    template<typename T1, typename T2>
    static signal_type process_slice(const T1& setup, const T2& data, const size_type a, const size_type b, const size_type c, const size_type d)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        #pragma HLS ARRAY_PARTITION variable=data dim=0

        signal_type result = false;

        if (a != b and a != c and a != d and b != c and b != d and c != d)
        {
            if (a >= setup.slice.minimum and a <= setup.slice.maximum)
            {
                if (b >= setup.slice.minimum and b <= setup.slice.maximum)
                {
                    if (c >= setup.slice.minimum and c <= setup.slice.maximum)
                    {
                        if (d >= setup.slice.minimum and d <= setup.slice.maximum)
                        {
                            result = data[0][a] and data[1][b] and data[2][c] and data[3][d];
                        }
                    }
                }
            }
        }
        return result;
    }

    template<typename T1, typename T2>
    static signal_type process(const size_type a, const size_type b, const T1& setup, const T2& data)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        signal_type result = false;

        for (size_type c = minimum; c < maximum; ++c)
        {
            #pragma HLS UNROLL
            for (size_type d = minimum; d < maximum; ++d)
            {
                #pragma HLS UNROLL
                result |= process_slice(setup, data, a, b, c, d);
            }
        }

        return result;
    }

    template<typename T1, typename T2>
    static signal_type process(const T1& setup, const T2& data)
    {
        #pragma HLS INTERFACE ap_none port=setup
        #pragma HLS INTERFACE ap_none port=data
        #pragma HLS INTERFACE ap_ctrl_none port=return

        signal_type result = false;

        for (size_type a = minimum; a < maximum; ++a)
        {
            #pragma HLS UNROLL
            for (size_type b = minimum; b < maximum; ++b)
            {
                #pragma HLS UNROLL
                result |= process(a, b, setup, data); // workaround to reduce memory load
            }
        }

        return result;
    }
}; // struct combine<4>

#endif
