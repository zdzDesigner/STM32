#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

#define LED_RCC  RCC_APB2Periph_GPIOB
#define LED_GPIO GPIOB
#define LED_PIN  GPIO_Pin_4

#define LED1_RCC  RCC_APB2Periph_GPIOD
#define LED1_GPIO GPIOD
#define LED1_PIN  GPIO_Pin_2

void LED_GPIO_Config(void);
void LED_Open(void);
void LED_Close(void);

void LED_Toggle(uint8_t flag);

void LED1_GPIO_Config(void);

#endif