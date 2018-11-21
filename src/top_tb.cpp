#include "top.h"

#include "xorshift32.h"
#include "xorshift128.h"

#include <cassert>
#include <cstddef>

int main()
{
    static const size_t frames = 128;

    xorshift32 gen32[output_type::size] = {
        {0x76067985}, {0x51e3bdc2}, {0xb161c400}, {0x07bc47c6},
        {0x80b7eb48}, {0x2118434a}, {0xcc67f0c4}, {0xc629320b},
    };

    xorshift128 gen128[output_type::size] = {
        {0x6a3f3b9e, 0x8b233c9e, 0x495e275e, 0xb487c1b6},
        {0x9684124a, 0xc690e0e2, 0xfa5c0eb8, 0x545b2ab0},
        {0x4113bd19, 0x12c9fed3, 0xcf03a852, 0x6c5f8f08},
        {0x1c130413, 0x10037764, 0xea7d5361, 0xca28e77c},
        {0xad50794e, 0x984198f4, 0xc1592139, 0x92626a19},
        {0x7f99ce53, 0x3844e303, 0x3d0e4d9e, 0x99f1f588},
        {0xc7515e1b, 0x0b1ddf55, 0xafc486b8, 0x33f5779d},
        {0xf61609ab, 0xfa1d9c03, 0xb2944ed5, 0x5b231ba1},
    };

    for (size_t frame = 0; frame < frames; ++frame)
    {
        input_type input = {};
        output_type output = {};

        top(input, output);

        for (size_t i = 0; i < output_type::size; ++i)
        {
            assert(gen32[i].next() == output.data32[i]);
            assert(gen128[i].next() == output.data128[i]);
        }
    }

    return 0;
}
