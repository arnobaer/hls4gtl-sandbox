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

struct charge_interface
{
    object_charge_vector charge_m2;
    object_charge_vector charge_m1;
    object_charge_vector charge_0;
    object_charge_vector charge_p1;
    object_charge_vector charge_p2;
};

struct object_logic
{
    object_interface oif;
    charge_interface cif;

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

        #pragma HLS array_partition variable=oif.vector_1 complete dim=0
        #pragma HLS array_partition variable=oif.vector_2 complete dim=0
        #pragma HLS array_partition variable=oif.vector_3 complete dim=0
        #pragma HLS array_partition variable=oif.vector_4 complete dim=0
        #pragma HLS array_partition variable=oif.vector_5 complete dim=0
        #pragma HLS array_partition variable=oif.vector_6 complete dim=0
        #pragma HLS array_partition variable=oif.vector_7 complete dim=0

        for (unsigned i = 0; i < T::size; ++i)
        {
            #pragma HLS unroll
            oif.vector_1[i] = pt_1.match(input.objects[2][i]);
            oif.vector_2[i] = pt_2.match(input.objects[2][i]);
            oif.vector_3[i] = pt_3.match(input.objects[1][i]); // -1bx
            oif.vector_4[i] = eta_1.match(input.objects[3][i]); // +1bx
            oif.vector_5[i] = oif.vector_1[i] and oif.vector_3[i] and oif.vector_4[i]; // combine filtered results
            oif.vector_6[i] = oif.vector_1[i] and oif.vector_2[i] and oif.vector_4[i];
            oif.vector_7[i] = oif.vector_2[i] and oif.vector_3[i];

        }

        #pragma HLS array_partition variable=cif.charge_m2 complete dim=0
        #pragma HLS array_partition variable=cif.charge_m1 complete dim=0
        #pragma HLS array_partition variable=cif.charge_0 complete dim=0
        #pragma HLS array_partition variable=cif.charge_p1 complete dim=0
        #pragma HLS array_partition variable=cif.charge_p2 complete dim=0

        // Store charges
        for (unsigned i = 0; i < T::size; ++i)
        {
            #pragma HLS unroll
            cif.charge_m2[i] = input.objects[0][i].charge;
            cif.charge_m1[i] = input.objects[1][i].charge;
            cif.charge_0[i] = input.objects[2][i].charge;
            cif.charge_p1[i] = input.objects[3][i].charge;
            cif.charge_p2[i] = input.objects[4][i].charge;
        }
    }
};

struct condition_interface
{
    ap_uint<1> condition_1;
    ap_uint<1> condition_2;
    ap_uint<1> condition_3;
    ap_uint<1> condition_4;
    ap_uint<1> condition_5;
    ap_uint<1> condition_6;
    ap_uint<1> condition_7;
    ap_uint<1> condition_8;
};

struct condition_logic
{
    condition_interface cif;

    template<typename T1>
    void process(const T1& ol)
    {
        #pragma HLS INTERFACE ap_none port=ol
        #pragma HLS INTERFACE ap_ctrl_none port=return

        // NOTE python style slices!
        const condition::combine::slice<0, 8>::chgcor<condition::ignore> condition_1 = { true };
        const condition::combine::slice<0, 8>::chgcor<condition::ignore> condition_2 = { false };
        const condition::combine::slice<0, 6>::chgcor<condition::like_sign> condition_3 = { true };
        const condition::combine::slice<0, 4>::chgcor<condition::opposite_sign> condition_4 = { false };
        const condition::combine::slice<0, 8>::chgcor<condition::ignore> condition_5 = { true };

        cif.condition_1 = condition_1.match(ol.oif.vector_2);
        cif.condition_2 = condition_2.match(ol.oif.vector_1);
        cif.condition_3 = condition_2.match(ol.oif.vector_2, ol.oif.vector_3,
                                            ol.cif.charge_0, ol.cif.charge_m1);
        cif.condition_4 = condition_2.match(ol.oif.vector_4, ol.oif.vector_4,
                                            ol.cif.charge_p1, ol.cif.charge_p1);
        cif.condition_5 = condition_4.match(ol.oif.vector_2, ol.oif.vector_2, ol.oif.vector_2,
                                            ol.cif.charge_0, ol.cif.charge_0, ol.cif.charge_0);
        cif.condition_6 = condition_4.match(ol.oif.vector_3, ol.oif.vector_2, ol.oif.vector_1,
                                            ol.cif.charge_m1, ol.cif.charge_0, ol.cif.charge_0);
        cif.condition_7 = condition_3.match(ol.oif.vector_4, ol.oif.vector_3, ol.oif.vector_2, ol.oif.vector_1,
                                            ol.cif.charge_p1, ol.cif.charge_m1, ol.cif.charge_0, ol.cif.charge_0);
        cif.condition_8 = condition_5.match(ol.oif.vector_2, ol.oif.vector_2, ol.oif.vector_2, ol.oif.vector_2,
                                            ol.cif.charge_0, ol.cif.charge_0, ol.cif.charge_0, ol.cif.charge_0);
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

        aif.l1_algorithm_1 = cl.cif.condition_1;
        aif.l1_algorithm_2 = not cl.cif.condition_2;
        aif.l1_algorithm_3 = cl.cif.condition_3;
        aif.l1_algorithm_4 = cl.cif.condition_1 and cl.cif.condition_3;
        aif.l1_algorithm_5 = cl.cif.condition_4;
        aif.l1_algorithm_6 = not cl.cif.condition_5;
        aif.l1_algorithm_7 = cl.cif.condition_5 or cl.cif.condition_6;
        aif.l1_algorithm_8 = cl.cif.condition_6 and cl.cif.condition_7 and cl.cif.condition_8;
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
