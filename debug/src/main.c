#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ws2812b.h"
#include "stm32f10x.h"

static void led()
{
    LED_GPIO_Config();
    LED_Open();

    // int count = 0;
    int i = 0;

    while (1) {
        if (i == 0) {
            i++;
            LED_Open();
        } else if (i == 1) {
            i--;
            LED_Close();
        }
        if (i == 10) {
            LED_FLAG_Toggle();
        }

        // count = 0;
        // while (count < 10000000) {
        //     count++;
        // }
    }
}

static void ws2812b()
{
    WS2812B_Init();
    WS2812B_ON();
}

// static int i = 0;
int main()
{
    delay_init();
    PRINT_Config();


    ws2812b();
    return 0;
}
