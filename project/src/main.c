#include "led.h"
#include "adc.h"
#include "delay.h"
#include "nrf24/nrf24.h"
#include "usart.h"
#include "util/scale.h"
#include "oledv2/oled.h"
#include "spi.h"

extern uint16_t ADC_VAL[2];
extern uint8_t  TX_BUF[TX_PLOAD_WIDTH]; // 发射数据缓存
extern uint8_t  RX_BUF[RX_PLOAD_WIDTH]; // 接收数据缓存

static uint8_t boot_nrf24()
{
    // CHECK_SPI_Config();
    SPI_NRF_Init();
    delay_ms(100);

    /*检测NRF模块与MCU的连接*/
    printf("NRF_READ_REG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG));
    printf("CONFIG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + CONFIG));
    printf("STATUS:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + STATUS));

    return NRF_Check();
}

/* 进入发送模式 */
static int send()
{

    uint8_t status = boot_nrf24();
    printf("status: %d\n", status);
    while (status != SUCCESS) {
        delay_ms(1000);
        printf("\r\n NRF与MCU连接失败，请重新检查接线！\r\n");
    }
    NRF_TX_Mode();
    delay_ms(100);

    ADC_Config();
    // old remote controller
    // Scaler scalerH = ScalerInit(0, 255, 1670, 2370);
    // Scaler scalerV = ScalerInit(0, 255, 1710, 2380);

    // new remote controller
    Scaler scalerH = ScalerInit(0, 255, 1740, 2430);
    Scaler scalerV = ScalerInit(0, 255, 1780, 2330);
    printf("%s\n", "adc send start");

    // delay_ms(100);

    u16 hval = 0;
    u16 vval = 0;
    while (1) {
        // printf("--------\n");
        delay_ms(100);
        ADC_DMA_Avg();
        /* 发送模式 */
        hval = scalerH.conv(&scalerH, ADC_VAL[0]);
        vval = scalerV.conv(&scalerV, ADC_VAL[1]);

        // printf("hval:%d,vval:%d\n", ADC_VAL[0], ADC_VAL[1]);

        printf("hval:%d,vval:%d\n", hval, vval);
        TX_BUF[0] = (uint8_t)hval;
        TX_BUF[1] = (uint8_t)vval;
        NRF_Tx_Dat(TX_BUF);
        // uint8_t NrfStatus = NRF_Tx_Dat(TX_BUF);
        // printf("%s\n", "send ");
        // printf("send after status:%d\n", NrfStatus);
    }
    return 0;
}

static int send_demo()
{
    while (1) {
        delay_ms(30);
        printf("ssssss ccc\n");
    }
    return 0;
}

static int receive()
{
    OLED_Init();
    OLED_Clear();
    OLED_Demo();

    uint8_t status = boot_nrf24();
    printf("status: %d\n", status);
    // 已初始的变量在常量区
    char statusstr[]   = "status:x";
    int  len           = sizeof(statusstr);
    statusstr[len - 2] = status + 48;
    OLED_Clear();
    OLED_ShowString(0, 0, statusstr);

    while (status != SUCCESS) {
        delay_ms(1000);
        printf("\r\n NRF与MCU连接失败，请重新检查接线！\r\n");
    }
    OLED_ShowString(0, 2, "nrf24 to mcu ok");
    NRF_RX_Mode(); // NRF 进入接收模式

    while (1) {
        NRF_Rx_Dat(RX_BUF);
        uint8_t hval = RX_BUF[0];
        uint8_t vval = RX_BUF[1];
        printf("%d,%d\n", hval, vval);
        OLED_Clear();
        OLED_ShowNum(0, 0, hval, 5, 20);
        OLED_ShowNum(56, 0, vval, 4, 20);
    }
    return 0;
}

static void Delay(uint32_t nTime)
{
    while (nTime--) {}
}
static int light(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Configure GPIOA Pin 1 as Output push-pull
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    while (1) {
        // Toggle the LED state
        GPIO_WriteBit(GPIOA, GPIO_Pin_3, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3)));
        Delay(1000000); // Delay for a while
    }
}

int main()
{
    // light();
    // return 0;
    // 定义中断组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    delay_init();
    PRINT_Config();
    LED_GPIO_Config();
    LED_Open();

    // return send();
    // return send_demo();
    return receive();
}
