#include "top.h"

int main()
{
    input_type input = {
      0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
      1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
      1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
      1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,
    };
    output_type output = {0, 0, 0, 0};

    // Add your test bench
    top(input, output);

    if (output.result[0] != true)
        return 1;
    if (output.result[1] != true)
        return 1;
    if (output.result[2] != true)
        return 1;
    if (output.result[3] != true)
        return 1;

    return 0;
}
