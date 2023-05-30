#include "stm32f10x_gpio.h"
#include "stm32f10x.h"

void GPIO_SetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin) {
  GPIOx->BSRR |= GPIO_Pin;
}

void GPIO_ResetBits(GPIO_TypeDef *GPIOx, unit16_t GPIO_Pin) {
  GPIOx->BRR |= GPIO_Pin;
}

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitObj) {

  GPIOSpeed_TypeDef speed = GPIO_InitObj->GPIO_Speed;
  GPIOMode_TypeDef mode = GPIO_InitObj->GPIO_Mode;
  unit32_t pin = (unit32_t)GPIO_InitObj->GPIO_Pin;

  // 保留低4位
  unit32_t modeL4 = mode & ((unit32_t)0x0F);
  // 输入模式 第4位为1
  if ((mode & (unit32_t)0x10) != 0x00) {
    modeL4 |= speed;
  }

  // 低8位
  if ((pin & (unit32_t)0x00FF) != 0x00) {

    // unit32_t tempreg = GPIOx->CRH;
    // unit32_t tempreg = GPIOx->CRL;
    for (unit32_t pinpos = 0x00; pinpos < 0x08; pinpos++) {
      unit32_t pos = ((unit32_t)0x01) << pinpos;
      unit32_t currentPin = pin & pos;
      // 0到8位滑动， 相同时匹配
      if (currentPin == pos) {
        // 左移两位，找到引脚地址（1个引脚占四位）
        // pos = pinpos << 2;
        // tempreg &= ~(((unit32_t)0x0F) << pos);
        // tempreg |= modeL4 << pos;
        // GPIOx->CRH &=~(0x0F<<(4*5)); // 配置输出模式, 偏移地址
        // GPIOx->CRH |=(1<<(4*5));
      }
    }
    // GPIOx->CRL = tempreg;
    // GPIOx->CRH = tempreg;
  }

  if (pin > 0x00FF) {
    // GPIOx->CRH &=~(0x0F<<(4*5)); // 配置输出模式, 偏移地址
    // GPIOx->CRH |=(1<<(4*5));
    unit32_t tempreg = GPIOx->CRH;
    for (unit32_t pinpos = 0x09; pinpos <= 0x0F; pinpos++) {
      unit32_t pos = ((unit32_t)0x01) << pinpos;
      unit32_t currentPin = GPIO_InitObj->GPIO_Pin & pos;
      // 0到8位滑动， 相同时匹配
      if (currentPin == pos) {
        // GPIOx->CRH &=~(0x0F<<(4*5)); // 配置输出模式, 偏移地址
        // GPIOx->CRH |=(1<<(4*5));
        // 左移两位，找到引脚地址（1个引脚占四位）
        pos = (pinpos - 8) << 2;
        tempreg &= ~(((unit32_t)0x0F) << pos);
        tempreg |= modeL4 << pos;
      }
    }
    GPIOx->CRH = tempreg;
  }
}

void vv(int a) {}
