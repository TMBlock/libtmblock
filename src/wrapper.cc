#include <HalideBuffer.h>
#include "tmblock.h"
#include "tmblock_pre_packed.h"
#include "tmblock_pre_planar.h"
#include "tmblock_post_packed.h"
#include "tmblock_post_planar.h"
#include "tmblock_embed_packed.h"
#include "tmblock_embed_planar.h"

typedef int GeneratedFunction(struct halide_buffer_t *, struct halide_buffer_t *,
        int32_t, int32_t, struct halide_buffer_t *);

static inline Halide::Runtime::Buffer<uint8_t> TM_Picture_to_Buffer(
        TM_Picture *pic) {
    int channels = pic->mode == TM_RGB ? 3 : 4;
    halide_dimension_t dimensions[] = {
        {0, pic->width, channels},
        {0, pic->height, pic->linesize},
        {0, channels, 1},
    };
    Halide::Runtime::Buffer<uint8_t> ret(pic->ptr, 3, dimensions);
    return ret;
}

static inline void validate_variables(TM_Picture *input, TM_Picture *logo,
        TM_Picture *output) {
    assert(input->mode == TM_RGB);
    assert(output->mode == TM_RGB);
    assert(logo->mode == TM_RGBA);
    assert(input->width == output->width);
    assert(input->height == output->height);
}

static inline int call_TM_Function(TM_Picture *input, TM_Picture *logo,
        int offset_x, int offset_y, TM_Picture *output, TM_Layout layout,
        GeneratedFunction *callbacks[]) {
    validate_variables(input, logo, output);
    auto input_buffer = TM_Picture_to_Buffer(input),
         logo_buffer = TM_Picture_to_Buffer(logo),
         output_buffer = TM_Picture_to_Buffer(output);
    return callbacks[layout](input_buffer, logo_buffer, offset_x, offset_y,
            output_buffer);
}

int TM_pre(TM_Picture *input, TM_Picture *logo, int offset_x,
        int offset_y, TM_Picture *output, TM_Layout layout) {
    static GeneratedFunction *callbacks[] = {
        tmblock_pre_planar, tmblock_pre_packed};
    return call_TM_Function(input, logo, offset_x, offset_y, output, layout,
            callbacks);
}

int TM_post(TM_Picture *input, TM_Picture *logo, int offset_x,
        int offset_y, TM_Picture *output, TM_Layout layout) {
    static GeneratedFunction *callbacks[] = {
        tmblock_post_planar, tmblock_post_packed};
    return call_TM_Function(input, logo, offset_x, offset_y, output, layout,
            callbacks);
}

int TM_embed(TM_Picture *input, TM_Picture *logo, int offset_x,
        int offset_y, TM_Picture *output, TM_Layout layout) {
    static GeneratedFunction *callbacks[] = {
        tmblock_embed_planar, tmblock_embed_packed};
    return call_TM_Function(input, logo, offset_x, offset_y, output, layout,
            callbacks);
}
