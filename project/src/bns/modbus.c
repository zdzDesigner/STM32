#include "bns/modbus.h"
#include "delay.h"

int modbus()
{

    while (1) {
        delay_ms(100);
        printf("{\"cmd\":3}\n");
    }
    return 0;
}
