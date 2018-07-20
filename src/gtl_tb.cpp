#include "gtl.h"
#include "comb_muon.h"

#include "gtl_tb_utils.h"

#include <cassert>
#include <iostream>
#include <fstream>

int main()
{
	input_t input = {};
	input.muons[0].et = 0x14;
	input.muons[1].et = 0x12;
	input.muons[2].et = 0x9;
	input.muons[3].et = 0x9;

	std::ifstream ifs("gtl_tb.dat");
	while (ifs.good())
	{
		ifs >> input.muons[0].et;

		output_t output;
		output.algorithms.fill(false);

		gtl(input, output);

		//assert(output.algorithms[0] == true);
		//assert(output.algorithms[1] == true);
		//assert(output.algorithms[2] == true);
		//assert(output.algorithms[3] == true);
		//assert(output.algorithms[4] == false);
		//assert(output.algorithms[5] == true);

		assert(output.final == false);


		std::cout << output << std::endl;
	}
}
