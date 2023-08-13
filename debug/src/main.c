#include "led.h"

static int i = 0;
int        main()
{

    LED_GPIO_Config();
    LED_Open();

    // int count = 0;
    // int i     = 0;

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

    return 0;
}
