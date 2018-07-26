#ifndef TMBLOCK_H
#define TMBLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum {
    TM_RGB,
    TM_RGBA,
} TM_PictureMode;

typedef struct {
    uint8_t *ptr;
    int width, height, linesize;
    TM_PictureMode mode;
} TM_Picture;

int TM_post(TM_Picture *input, TM_Picture *logo, int offset_x,
            int offset_y, TM_Picture *output);
int TM_pre(TM_Picture *input, TM_Picture *logo, int offset_x,
           int offset_y, TM_Picture *output);
int TM_embed(TM_Picture *input, TM_Picture *logo, int offset_x,
             int offset_y, TM_Picture *output);

#ifdef __cplusplus
}
#endif

#endif
