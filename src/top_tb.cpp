#include "top.h"

bool test_combine(const size_t dim, const size_t min, const size_t max)
{
    const setup_type setup = {dim, {min, max}};

    const input_type input = {{
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0}, // first object vector
      {0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0}, // second object vector
      {0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0}, // third object vector
      {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, // fourth object vector
    }};

    output_type output = {0};

    top(setup, input, output);

    return output.result;
}

int main()
{
    if (false == test_combine(1, 0, 7))
        return 1;

    if (false == test_combine(2, 4, 11))
        return 2;

    if (false == test_combine(3, 0, 11))
        return 3;

    if (false == test_combine(4, 0, 11))
        return 4;

    return 0;
}
