#ifndef hls4gtl_types_h
#define hls4gtl_types_h

#include <ap_int.h>

#define N_MUONS 8

#define N_EGS  12
#define N_TAUS 12
#define N_JETS 12

#define N_ALGORITHMS 512

typedef ap_uint<1> bool_t;

struct object_t
{
};

typedef ap_uint<12> muon_et_t;
typedef ap_uint<2> muon_iso_t;
typedef ap_uint<2> muon_quality_t;

struct muon_t : object_t
{
	muon_et_t et;
	muon_iso_t iso;
	muon_quality_t quality;
};

struct muon_req_t
{
	muon_et_t et_threshold;
	muon_iso_t iso;
	muon_quality_t quality;
};

typedef ap_uint<14> calo_pt_t;

struct calo_t : object_t
{
	calo_pt_t pt;
};

struct calo_req_t
{
	calo_pt_t pt_threshold;
};

// GTL inputs
struct input_t
{
	muon_t muons[N_MUONS];
	calo_t egs[N_EGS];
	calo_t taus[N_TAUS];
	calo_t jets[N_JETS];

};

// GTL outputs
struct output_t
{
	bool_t algorithms[N_ALGORITHMS];
	bool_t final;
};

#endif
