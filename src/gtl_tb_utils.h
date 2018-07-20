#ifndef gtl_tb_utils
#define gtl_tb_utils

#include <iostream>
#include <map>
#include <string>

std::ostream& operator<<(std::ostream& os, const bool_t& state)
{
	static const std::map<bool_t, std::string> literals{
		{false, "false"}, {true, "true"}
	};
	os << literals.at(state);
	return os;
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const ap_array<T, N>& array)
{
	for (size_t i = 0; i < array.size(); ++i)
	{
		os << "[" << i << "] = " << array.at(i) << "\n";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const output_t& output)
{
	os << output.algorithms;
	os << "FinalOR = " << output.final << "\n";
	return os;
}

#endif
