#include <stdio.h>
#include "Halide.h"

using namespace Halide;

class PreTMBlockGenerator : public Halide::Generator<PreTMBlockGenerator> {
   public:
    Input<Buffer<uint8_t>> input{"input", 3};
    Input<Buffer<uint8_t>> logo{"logo", 3};

    Output<Buffer<uint8_t>> output{"output", 3};

    Func logo_ext{"logo_ext"}, input_f{"input_f"}, logo_f{"logo_f"};

    Var x, y, ch;

    void generate() {
        input_f(x, y, ch) = cast<float>(input(x, y, ch));
        logo_ext = BoundaryConditions::constant_exterior(
            logo, 0, logo.dim(0).min(), logo.dim(0).max(), logo.dim(1).min(),
            logo.dim(1).max());
        logo_f(x, y, ch) = cast<float>(logo_ext(x, y, ch));
        Expr alpha = logo_f(x, y, 3) / 255;
        output(x, y, ch) = cast<uint8_t>(
            select(alpha != 1,
                   clamp(input_f(x, y, ch) / (1 - alpha) -
                             logo_f(x, y, ch) * alpha / (1 - alpha),
                         0, 255),
                   input_f(x, y, ch)));
    }

    void schedule() { output.compute_root(); }
};

HALIDE_REGISTER_GENERATOR(PreTMBlockGenerator, tmblock_pre)
