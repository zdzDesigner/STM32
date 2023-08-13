#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

// 陈金的开发板为GPIOB 12
#define PIN      GPIO_Pin_12
#define RCC_GPIO (1 << 3)
#define GPIOX    GPIOB
int main()
{

    RCC->APB2ENR |= RCC_GPIO; // 打开时钟
    GPIO_InitTypeDef GPIO_InitObj;
    GPIO_InitObj.GPIO_Pin   = PIN;
    GPIO_InitObj.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitObj.GPIO_Speed = GPIO_SPeed_50MHZ;
    GPIO_Init(GPIOX, &GPIO_InitObj);
    GPIO_SetBits(GPIOX, PIN);

    int count = 0;
    int i     = 0;

    while (1) {
        if (i == 0) {
            i++;
            GPIO_ResetBits(GPIOX, PIN);
        } else {
            i--;
            // GPIO_SetBits(GPIOX, PIN);
        }
        count = 0;
        while (count < 100000) {
            count++;
        }
    }
}

// 无法debug 定位到main 
void SystemInit(void) {}
