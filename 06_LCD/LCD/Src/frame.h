#ifndef __FRAME_H__
#define __FRAME_H__

#include "stm32f7xx_hal.h"

#define FRAME_START     0x7D
#define FRAME_END       0x7D
#define FRAME_ESC       0x7E

int32_t frame_encode(const char *src, uint16_t src_len, char *dst, uint16_t *dst_len);
int32_t frame_decode(const char *src, uint16_t src_len, char *dst, uint16_t *dst_len); 

#endif//__FRAME_H__
