#include <HalideBuffer.h>
#include "tmblock.h"
#include "tmblock_embed.h"
#include "tmblock_post.h"
#include "tmblock_pre.h"

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

int TM_post(TM_Picture *input, TM_Picture *logo, int offset_x,
             int offset_y, TM_Picture *output) {
    validate_variables(input, logo, output);
    auto input_buffer = TM_Picture_to_Buffer(input),
         logo_buffer = TM_Picture_to_Buffer(logo),
         output_buffer = TM_Picture_to_Buffer(output);
    return tmblock_post(input_buffer, logo_buffer, offset_x, offset_y,
                        output_buffer);
}

int TM_pre(TM_Picture *input, TM_Picture *logo, int offset_x,
            int offset_y, TM_Picture *output) {
    validate_variables(input, logo, output);
    auto input_buffer = TM_Picture_to_Buffer(input),
         logo_buffer = TM_Picture_to_Buffer(logo),
         output_buffer = TM_Picture_to_Buffer(output);
    return tmblock_pre(input_buffer, logo_buffer, offset_x, offset_y,
                       output_buffer);
}

int TM_embed(TM_Picture *input, TM_Picture *logo, int offset_x,
                  int offset_y, TM_Picture *output) {
    validate_variables(input, logo, output);
    auto input_buffer = TM_Picture_to_Buffer(input),
         logo_buffer = TM_Picture_to_Buffer(logo),
         output_buffer = TM_Picture_to_Buffer(output);
    return tmblock_embed(input_buffer, logo_buffer, offset_x, offset_y,
                             output_buffer);
}
