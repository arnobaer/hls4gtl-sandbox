#ifndef hls4gtl_sandbox_types_h
#define hls4gtl_sandbox_types_h

#include "utils.hxx"

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
