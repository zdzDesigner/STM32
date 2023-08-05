#include "led.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

int main()
{
    // 定义中断组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    delay_init();
    PRINT_Config();
    LED_GPIO_Config();

    ADC_Config();

    while (1) {
    }
}
