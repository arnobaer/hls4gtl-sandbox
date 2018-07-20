#ifndef hls4gtl_types_h
#define hls4gtl_types_h

#include <ap_int.h>
#include "ap_array.h"

#define N_MUONS 8

#define N_EGS  12
#define N_TAUS 12
#define N_JETS 12

#define N_ALGORITHMS 512

typedef ap_uint<1> bool_t;

struct object_t
{
};

struct muon_t : object_t
{
	typedef ap_uint<12> muon_et_t;
	typedef ap_uint<2> muon_iso_t;
	typedef ap_uint<2> muon_quality_t;

	muon_et_t et;
	muon_iso_t iso;
	muon_quality_t quality;

	muon_t(): et(0), iso(0), quality(0) {}

	struct cuts_t
	{
		muon_et_t et_threshold;
		muon_iso_t iso;
		muon_quality_t quality;

		cuts_t(): et_threshold(0), iso(0), quality(0) {}
		cuts_t(muon_et_t et_threshold, muon_iso_t iso, muon_quality_t quality):
			et_threshold(et_threshold), iso(iso), quality(quality) {}
	};
};

typedef ap_uint<14> calo_pt_t;

struct calo_t : object_t
{
	typedef ap_uint<14> calo_pt_t;

	calo_pt_t pt;

	calo_t(): pt(0) {}

	struct cuts_t
	{
		calo_pt_t pt_threshold;

		cuts_t(): pt_threshold(0) {}
	};
};

typedef ap_array<muon_t, N_MUONS> muon_vector_t;
typedef ap_array<calo_t, N_EGS> eg_vector_t;
typedef ap_array<calo_t, N_TAUS> tau_vector_t;
typedef ap_array<calo_t, N_JETS> jet_vector_t;

// GTL inputs
struct input_t
{
	muon_vector_t muons;
	eg_vector_t egs;
	tau_vector_t taus;
	jet_vector_t jets;
};

// GTL outputs
struct output_t
{
	ap_array<bool_t, N_ALGORITHMS> algorithms;
	bool_t final;
};

#endif
