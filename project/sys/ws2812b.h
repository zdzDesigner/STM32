#ifndef __WS2812B_H
#define __WS2812B_H
#include "stm32f10x.h"

void WS2812B_OFF(void);
void WS2812B_ON(void);
void WS2812B_Init(void);
void WS2812B_Gradient(void);
void WS2812B_Color(char *str);
void WS2812B_Compute(uint8_t hval, uint8_t vval);

#endif
