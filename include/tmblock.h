#ifndef TMBLOCK_TMBLOCK_H
#define TMBLOCK_TMBLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "./tmlayout.h"

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
            int offset_y, TM_Picture *output, TM_Layout layout);
int TM_pre(TM_Picture *input, TM_Picture *logo, int offset_x,
           int offset_y, TM_Picture *output, TM_Layout layout);
int TM_embed(TM_Picture *input, TM_Picture *logo, int offset_x,
             int offset_y, TM_Picture *output, TM_Layout layout);

typedef int TM_Function(TM_Picture *input, TM_Picture *logo, int offset_x,
             int offset_y, TM_Picture *output, TM_Layout layout);

#ifdef __cplusplus
}
#endif

#endif
