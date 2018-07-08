#include <stdio.h>
#include "Halide.h"

using namespace Halide;

class TMBlockGenerator : public Halide::Generator<TMBlockGenerator> {
   public:
    Input<Buffer<uint8_t>> input{"input", 3};
    Input<Buffer<uint8_t>> logo{"logo", 3};

    Output<Buffer<uint8_t>> output{"output", 3};

    Func logo_ext{"logo_ext"}, input_f{"input_f"}, logo_f{"logo_f"};

    Var x, y, ch;

    void generate() {
        input_f(x, y, ch) = cast<float>(input(x, y, ch));
        logo_ext = BoundaryConditions::constant_exterior(logo, 0);
        logo_f(x, y, ch) = cast<float>(logo_ext(x, y, ch));
        Expr alpha = logo_f(x, y, 4) / 255;
        output(x, y, ch) =
            cast<uint8_t>(input_f(x, y, ch) / (1 - alpha) -
                          logo_f(x, y, ch) * alpha / (1 - alpha));
    }

    void schedule() { output.compute_root(); }
};

HALIDE_REGISTER_GENERATOR(TMBlockGenerator, tmblock)
