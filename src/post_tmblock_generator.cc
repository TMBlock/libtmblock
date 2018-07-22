#include "tmblock_generator-impl.h"

class PostCore {
   public:
    static inline Expr calc(Expr input, Expr logo, Expr alpha) {
        return select(alpha != 1, input - alpha * logo / (1 - alpha), input);
    }
};

HALIDE_REGISTER_GENERATOR(TMBlockGenerator<PostCore>, tmblock_post)
