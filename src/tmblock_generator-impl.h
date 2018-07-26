#pragma once
#include "Halide.h"

using namespace Halide;

template <typename Core>
class TMBlockGenerator : public Halide::Generator<TMBlockGenerator<Core>> {
   public:
    // XXX: why Input and Output is not working here?
    GeneratorInput<Buffer<uint8_t>> input{"input", 3}, logo{"logo", 3};
    GeneratorInput<int> offset_x{"offset_x"}, offset_y{"offset_y"};
    GeneratorOutput<Buffer<uint8_t>> output{"output", 3};

    Func logo_ext{"logo_ext"}, input_f{"input_f"}, logo_f{"logo_f"};

    Var x, y, ch;

    void generate() {
        input_f(x, y, ch) = cast<float>(input(x, y, ch));
        logo_ext = BoundaryConditions::constant_exterior(
            logo, 0, logo.dim(0).min(), logo.dim(0).max(), logo.dim(1).min(),
            logo.dim(1).max());
        logo_f(x, y, ch) =
            cast<float>(logo_ext(x - offset_x, y - offset_y, ch));
        Expr alpha = logo_f(x, y, 3) / 255;
        Expr result = Core::calc(input_f(x, y, ch), logo_f(x, y, ch), alpha);
        output(x, y, ch) = cast<uint8_t>(clamp(result, 0, 255));
    }

    void schedule() {
        // XXX(huiyiqun) Assume packed (or interleaved) layout here.
        // Should support more layout with a GeneratorParam.
        // See: http://halide-lang.org/tutorials/tutorial_lesson_16_rgb_generate.html
        input
            .dim(0).set_stride(3)
            .dim(2).set_stride(1);
        logo
            .dim(0).set_stride(4)
            .dim(2).set_stride(1);
        output
            .dim(0).set_stride(3)
            .dim(2).set_stride(1);

        output.compute_root();
    }
};
