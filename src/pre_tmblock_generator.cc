#include "tmblock_generator-impl.h"

struct PreCore {
    static inline Expr calc(Expr input, Expr logo, Expr alpha) {
        return select(alpha != 1,
                      input / (1 - alpha) - logo * alpha / (1 - alpha), input);
    }
};

HALIDE_REGISTER_GENERATOR(TMBlockGenerator<PreCore>, tmblock_pre)
