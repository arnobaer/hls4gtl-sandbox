#include "top.h"

int main()
{
    input_type input = {
      0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0,
      0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
      0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0,
    };
    output_type output = {0, 0, 0, 0};

    top(input, output);

    for (output_type::size_type i = 0; i < output_type::size; ++i)
    {
        if (output.result[i] != true)
            return 1;
    }

    return 0;
}
