// #include "led.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "util/scale.h"
#include "nrf24/nrf24.h"

extern uint16_t ADC_VAL[2];
extern uint8_t TX_BUF[RX_PLOAD_WIDTH];

static int send()
{
    /* 进入发送模式 */
    ADC_Config();
    Scaler scaler = ScalerInit(0, 255, 1740, 2400);
    printf("%s\n", "adc send start");
    NRF_TX_Mode();
    delay_ms(100);

    u16 hval = 0;
    u16 vval = 0;
    while (1) {
        delay_ms(10);
        /* 发送模式 */
        hval = scaler.conv(&scaler, ADC_VAL[0]);
        vval = scaler.conv(&scaler, ADC_VAL[1]);

        printf("hval:%d,vval:%d\n", hval, vval);
        TX_BUF[0] = (uint8_t)hval;
        TX_BUF[1] = (uint8_t)vval;
        // NRF_Tx_Dat(TX_BUF);
        uint8_t NrfStatus = NRF_Tx_Dat(TX_BUF);
        // printf("%s\n", "send ");
        // printf("send after status:%d\n", NrfStatus);
    }
    return 0;
}

static int send2()
{
    while (1) {
        delay_ms(300);
        printf("ssssss");
    }
    return 0;
}

int main()
{
    // 定义中断组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    delay_init();
    PRINT_Config();
    // LED_GPIO_Config();

    // return send();
    return send2();
}
