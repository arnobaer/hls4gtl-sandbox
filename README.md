# hls4gtl-sandbox

Exploring Vivado HLS

## Usage

    $ git clone https://github.com/arnobaer/hls4gtl-sandbox.git
    $ git checkout <branch/tag>
    $ python manage.py <command>

### Commands

 - `csim` run C simulation
 - `csynth` run C synthesis
 - `cosim` run co-simulation
 - `export` run export IP core
 - `clean` remove project/solution

Default solution clock is 24ns.

## Add sandbox code

1) add inputs and outputs to structs in file `src/types.h`

```c++
struct input_type
{
    // add inputs
    bool data;
};

struct output_type
{
    // add outputs
    bool result;
};
```
2) add logic code in file `src/top.cpp`

```c++
void top(const input_type& input, output_type& output)
{
    // add code
    output.result = ! input.data;
}
```
3) add test bench in file `src/top_tb.cpp`

```c++
void main()
{
    // add test bench

    input_type input;
    output_type output;

    input.data = false;
    top(input, output);

    return (input.data != output.result);
}
```
