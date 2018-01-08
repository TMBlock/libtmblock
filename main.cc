#include <iostream>

#include <cassert>
#include <cstring>
#include "HalideBuffer.h"
#include "halide_image_io.h"
#include "tmblock.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input> <logo_file> <output>"
                  << std::endl;
        return -1;
    }

    Halide::Runtime::Buffer<uint8_t> input = Halide::Tools::load_image(argv[1]),
                                     logo = Halide::Tools::load_image(argv[2]);
    Halide::Runtime::Buffer<uint8_t> output(
        input.dim(0).extent(), input.dim(1).extent(), input.dim(2).extent());

    tmblock(input, logo, output);

    for (int i = 0; i < input.dimensions(); i++) {
        auto dim = input.dim(i);
        std::cout << i << ' ' << dim.min() << ' ' << dim.max() << ' '
                  << dim.stride() << ' ' << dim.extent() << std::endl;
    }

    for (int i = 0; i < logo.dimensions(); i++) {
        auto dim = logo.dim(i);
        std::cout << i << ' ' << dim.min() << ' ' << dim.max() << ' '
                  << dim.stride() << ' ' << dim.extent() << std::endl;
    }

    return 0;
}
