#include "sys.h"

int main()
{
    // 定义中断组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    delay_init();
    PRINT_Config();
    LED_GPIO_Config();

    // led
    LED_Open();
    while (1) {
        delay_ms(300);
        LED_FLAG_Toggle();
    }


}
