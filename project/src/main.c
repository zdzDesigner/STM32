#include "led.h"
#include "delay.h"

int main()
{

    delay_init();
    LED_GPIO_Config();
    // led
    LED_Open();
    while (1) {
        delay_ms(300);
        LED_FLAG_Toggle();
    }
}
