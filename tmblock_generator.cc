#include <stdio.h>
#include "Halide.h"

using namespace Halide;

class TMBlockGenerator : public Halide::Generator<TMBlockGenerator> {
   public:
    Input<Buffer<uint8_t>> logo{"logo", 3};
    Input<Buffer<uint8_t>> input{"input", 3};

    Output<Buffer<uint8_t>> output{"output", 3};

    Func logo_ext{"logo_ext"};

    Var x, y, ch;

    void generate() {
        logo_ext = BoundaryConditions::constant_exterior(logo, 0);
        Expr alpha = logo_ext(x, y, 4);
        output(x, y, ch) = input(x, y, ch) / (1 - alpha) -
                           logo_ext(x, y, ch) * alpha / (1 - alpha);
    }

    void schedule() { output.compute_root(); }
};

HALIDE_REGISTER_GENERATOR(TMBlockGenerator, tmblock)
