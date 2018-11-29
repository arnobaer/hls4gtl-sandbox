#ifndef impl_hxx
#define impl_hxx

namespace impl {

struct object_interface
{
    object_match_vector vector_1;
    object_match_vector vector_2;
    object_match_vector vector_3;
    object_match_vector vector_4;
    object_match_vector vector_5;
    object_match_vector vector_6;
    object_match_vector vector_7;
};

struct object_logic
{
    object_interface oif;

    template<typename T>
    void process(const T& input)
    {
        #pragma HLS INTERFACE ap_none port=input
        #pragma HLS INTERFACE ap_ctrl_none port=return
        #pragma HLS array_partition variable=input.objects complete dim=0

        const pt_comparator pt_1(42);
        const pt_comparator pt_2(12);
        const pt_comparator pt_3(8, pt_comparator::eq);
        const eta_comparator eta_1(100, 200);

        for (unsigned i = 0; i < 8; ++i)
        {
            #pragma HLS unroll
            oif.vector_1[i] = pt_1.match(input.objects[2][i]);
            oif.vector_2[i] = pt_2.match(input.objects[2][i]);
            oif.vector_3[i] = pt_3.match(input.objects[1][i]); // -1bx
            oif.vector_4[i] = eta_1.match(input.objects[3][i]); // +1bx
            oif.vector_5[i] = oif.vector_1[i] and oif.vector_3[i] and oif.vector_4[i];
            oif.vector_6[i] = oif.vector_1[i] and oif.vector_2[i] and oif.vector_4[i];
            oif.vector_7[i] = oif.vector_2[i] and oif.vector_3[i];
        }
    }
};

struct condition_interface
{
    ap_uint<1> condition_match_1;
    ap_uint<1> condition_match_2;
    ap_uint<1> condition_match_3;
    ap_uint<1> condition_match_4;
    ap_uint<1> condition_match_5;
    ap_uint<1> condition_match_6;
};

struct condition_logic
{
    condition_interface cif;

    template<typename T, typename A, typename B, typename C>
    void process(const T& ol, const A& chgcor_double, const B& chgcor_triple, const C& chgcor_quad)
    {
        #pragma HLS INTERFACE ap_none port=ol
        #pragma HLS INTERFACE ap_ctrl_none port=return

        const condition cnd_1 = { 0, 8, condition::ignore }; // python style slices!
        const condition cnd_2 = { 0, 8, condition::ignore };
        const condition cnd_3 = { 0, 6, condition::positive };
        const condition cnd_4 = { 0, 4, condition::negative };

        cif.condition_match_1 = cnd_1.match(ol.oif.vector_2);
        cif.condition_match_2 = cnd_2.match(ol.oif.vector_1);
        cif.condition_match_3 = cnd_3.match(ol.oif.vector_2, ol.oif.vector_3, chgcor_double);
        cif.condition_match_4 = cnd_3.match(ol.oif.vector_4, ol.oif.vector_4, chgcor_double);
        cif.condition_match_5 = cnd_4.match(ol.oif.vector_5, ol.oif.vector_6, ol.oif.vector_7, chgcor_triple);
        cif.condition_match_6 = cnd_4.match(ol.oif.vector_2, ol.oif.vector_5, ol.oif.vector_6, chgcor_triple);
    }
};

struct algorithm_interface
{
    ap_uint<1> l1_algorithm_1;
    ap_uint<1> l1_algorithm_2;
    ap_uint<1> l1_algorithm_3;
    ap_uint<1> l1_algorithm_4;
    ap_uint<1> l1_algorithm_5;
    ap_uint<1> l1_algorithm_6;
    ap_uint<1> l1_algorithm_7;
    ap_uint<1> l1_algorithm_8;
};

struct algorithm_logic
{
    algorithm_interface aif;

    template<typename T>
    void process(const T& cl)
    {
        #pragma HLS INTERFACE ap_none port=cl
        #pragma HLS INTERFACE ap_ctrl_none port=return

        aif.l1_algorithm_1 = cl.cif.condition_match_1;
        aif.l1_algorithm_2 = not cl.cif.condition_match_2;
        aif.l1_algorithm_3 = cl.cif.condition_match_3;
        aif.l1_algorithm_4 = cl.cif.condition_match_1 and cl.cif.condition_match_3;
        aif.l1_algorithm_5 = cl.cif.condition_match_4;
        aif.l1_algorithm_6 = not cl.cif.condition_match_5;
        aif.l1_algorithm_7 = cl.cif.condition_match_5 or cl.cif.condition_match_6;
        aif.l1_algorithm_8 = cl.cif.condition_match_6;
    }

    template<typename T, size_t N>
    void map(T (&algorithms)[N]) const
    {
        #pragma HLS INTERFACE ap_none port=algorithms
        #pragma HLS INTERFACE ap_ctrl_none port=return
        #pragma HLS array_partition variable=algorithms complete dim=0

        algorithms[0] = aif.l1_algorithm_1;
        algorithms[1] = aif.l1_algorithm_3;
        algorithms[2] = aif.l1_algorithm_5;
        algorithms[3] = aif.l1_algorithm_7;
        algorithms[4] = aif.l1_algorithm_8;
        algorithms[5] = aif.l1_algorithm_6;
        algorithms[6] = aif.l1_algorithm_4;
        algorithms[7] = aif.l1_algorithm_2;
    }
};

} // namespace impl

#endif
