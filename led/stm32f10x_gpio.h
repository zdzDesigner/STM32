#ifndef __STM32F10X_GPIO_H__
#define __STM32F10X_GPIO_H__

#include "stm32f10x.h"

// 左移 0b000000001 1
// 左移 0b000000010 2
// 左移 0b000000100 4
// 左移 0b000001000 8
// 左移 0b000010000 16
#define GPIO_Pin_0 ((unit16_t)0x0001) // 低8位 &0x00FF != 0x00
#define GPIO_Pin_1 ((unit16_t)0x0002)
#define GPIO_Pin_2 ((unit16_t)0x0004)
#define GPIO_Pin_3 ((unit16_t)0x0008)
#define GPIO_Pin_4 ((unit16_t)0x0010)
#define GPIO_Pin_5 ((unit16_t)0x0020)
#define GPIO_Pin_6 ((unit16_t)0x0040)
#define GPIO_Pin_7 ((unit16_t)0x0080)
#define GPIO_Pin_8 ((unit16_t)0x0100) // 高8位
#define GPIO_Pin_9 ((unit16_t)0x0200)
#define GPIO_Pin_10 ((unit16_t)0x0400)
#define GPIO_Pin_11 ((unit16_t)0x0800)
#define GPIO_Pin_12 ((unit16_t)0x1000)
#define GPIO_Pin_13 ((unit16_t)0x2000) // 1<<13
#define GPIO_Pin_14 ((unit16_t)0x4000)
#define GPIO_Pin_15 ((unit16_t)0x8000)
#define GPIO_Pin_all ((unit16_t)0xFFFF)

typedef enum {
  GPIO_Speed_10MHZ = 1, // 01
  GPIO_SPeed_2MHZ,      // 10
  GPIO_SPeed_50MHZ,     // 11
} GPIOSpeed_TypeDef;

typedef enum {
  GPIO_Mode_Out_PP = 0x10,
} GPIOMode_TypeDef;

typedef struct {
  unit16_t GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
} GPIO_InitTypeDef;

void GPIO_SetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin);
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void vv();

#endif
