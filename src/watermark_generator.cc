#include "tmblock_generator-impl.h"

class WatermarkCore {
   public:
    static inline Expr calc(Expr input, Expr logo, Expr alpha) {
        return input * (1 - alpha) + logo * alpha;
    }
};

HALIDE_REGISTER_GENERATOR(TMBlockGenerator<WatermarkCore>, watermark)
