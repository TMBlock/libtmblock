#ifndef TMBLOCK_H
#define TMBLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    RGB,
    RGBA,
} TM_PictureMode;

typedef struct {
    uint8_t *ptr;
    int width, height, linesize;
    TM_PictureMode mode;
} TM_Picture;

bool TM_post(TM_Picture *input, TM_Picture *logo, size_t offset_x,
             size_t offset_y, TM_Picture *output);
bool TM_pre(TM_Picture *input, TM_Picture *logo, size_t offset_x,
            size_t offset_y, TM_Picture *output);
bool TM_embed(TM_Picture *input, TM_Picture *logo, size_t offset_x,
              size_t offset_y, TM_Picture *output);

#ifdef __cplusplus
}
#endif

#endif
