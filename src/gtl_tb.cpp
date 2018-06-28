#include "gtl.h"
#include "comb_muon.h"

#include <cassert>
#include <iostream>

int main()
{
	input_t input = {};
	input.muons[0].et = 0x14;
	input.muons[1].et = 0x12;
	input.muons[2].et = 0x9;
	input.muons[3].et = 0x9;

	output_t output = {};

	gtl(input, output);

	assert(output.algorithms[0] == true);
	assert(output.algorithms[1] == true);
	assert(output.algorithms[2] == true);
	assert(output.algorithms[3] == true);
	assert(output.algorithms[4] == false);
	assert(output.algorithms[5] == true);

	assert(output.final == true);

	for (size_t i = 0; i < N_ALGORITHMS; ++i)
	{
		std::cout << i << " " << output.algorithms[i] << std::endl;
	}

	std::cout << "FinalOR: " << output.final << std::endl;
}
