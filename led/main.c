#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

// 陈金的开发板为GPIOB 12
int main() {
  // RCC->APB2ENR |= (1 << 4);         // 打开GPIOC时钟
  // GPIOC->CRH &= ~(0x0F << (4 * 5)); // 配置输出模式, 偏移地址
  // GPIOC->CRH |= (1 << (4 * 5));
  // GPIOC->ODR &= ~(1 << 13); // 配置输出低电平
  // GPIOC->ODR |= (1 << 13);  // 配置输出高电平

  RCC->APB2ENR |= (1 << 4); // 打开GPIOC时钟
  GPIO_InitTypeDef GPIO_InitObj;
  GPIO_InitObj.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitObj.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitObj.GPIO_Speed = GPIO_SPeed_50MHZ;
  GPIO_Init(GPIOC, &GPIO_InitObj);
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
  // GPIO_SetBits(GPIOC, GPIO_Pin_13);
  while (1) {
  }
}

void SystemInit(void) {}
