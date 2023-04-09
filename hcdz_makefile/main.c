#include "main.h"

int main() {
  RCC->APB2ENR |= (1 << 4);         // 打开GPIOC时钟
  GPIOC->CRH &= ~(0x0F << (4 * 5)); // 配置输出模式, 偏移地址
  GPIOC->CRH |= (1 << (4 * 5));
  GPIOC->ODR &= ~(1 << 13); // 配置输出低电平
  // GPIOC->ODR |= (1 << 13); // 配置输出低电平


  while (1) {
  }
}

void SystemInit(void) {}
