#include <iostream>

#include <cassert>
#include <cstring>
#include "HalideBuffer.h"
#include "halide_image_io.h"
#include "tmblock_pre.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input> <logo_file> <output>"
                  << std::endl;
        return -1;
    }

    Halide::Runtime::Buffer<uint8_t> input = Halide::Tools::load_image(argv[1]),
                                     logo = Halide::Tools::load_image(argv[2]);
    Halide::Runtime::Buffer<uint8_t> output(
        input.dim(0).max() - input.dim(0).min() + 1,
        input.dim(1).max() - input.dim(1).min() + 1,
        input.dim(2).max() - input.dim(2).min() + 1);

    tmblock_pre(input, logo, 0, 0, output);

    Halide::Tools::save_image(output, argv[3]);

    return 0;
}
