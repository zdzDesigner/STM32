#include "led.h"
#include "adc.h"
#include "delay.h"
#include "nrf24/nrf24.h"
#include "usart.h"
#include "util/scale.h"
#include "oledv2/oled.h"
#include "pwm.h"
#include "ws2812b.h"
#include "spi.h"
#include <stdint.h>

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

    WS2812B_Init();

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
    Scaler scalerH = ScalerInit(0, 255, 1730, 2370);
    Scaler scalerV = ScalerInit(0, 255, 1740, 2355);
    // 2 ====
    // Scaler scalerH = ScalerInit(0, 255, 1750, 2430);
    // Scaler scalerV = ScalerInit(0, 255, 1730, 2255);
    printf("%s\n", "adc send start");

    // delay_ms(100);

    u16 hval = 0;
    u16 vval = 0;
    while (1) {
        // WS2812B_ON();
        // WS2812B_Color("red");

        // printf("--------\n");
        delay_ms(50);
        ADC_DMA_Avg();
        /* 发送模式 */
        hval = scalerH.conv(&scalerH, ADC_VAL[0]);
        vval = scalerV.conv(&scalerV, ADC_VAL[1]);

        // printf("hval:%d,vval:%d\n", ADC_VAL[0], ADC_VAL[1]);

        printf("hval:%d,vval:%d\n", hval, vval);
        TX_BUF[0] = (uint8_t)hval;
        TX_BUF[1] = (uint8_t)vval;
        // delay_ms(100);
        NRF_Tx_Dat(TX_BUF);
        WS2812B_Compute((uint8_t)hval, (uint8_t)vval);

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
    printf("status: %s\n", "nrf24 to mcu ok");
    OLED_ShowString(0, 2, "nrf24 to mcu ok");
    NRF_RX_Mode(); // NRF 进入接收模式

    PWM_Config(1);
    uint8_t dir       = 0; // 0:h, h:v
    uint8_t cv        = 125;
    uint8_t ecv       = 125;
    Scaler  scalerCV  = ScalerInit(80, 125, 0, 125);
    Scaler  scalerECV = ScalerInit(20, 80, 0, 125);

    uint8_t stop_min = 105;
    uint8_t stop_max = 150;

    while (1) {
        NRF_Rx_Dat(RX_BUF);
        uint8_t hval = RX_BUF[0];
        uint8_t vval = RX_BUF[1];
        // printf("%d,%d\n", hval, vval);
        OLED_Clear();
        OLED_ShowNum(0, 0, hval, 5, 20);
        OLED_ShowNum(56, 0, vval, 4, 20);

        // 前-左
        // GPIO_SetBits(GPIOA, GPIO_Pin_0);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_0);

        // GPIO_SetBits(GPIOA, GPIO_Pin_1);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_1);

        // GPIO_SetBits(GPIOA, GPIO_Pin_2);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_2);

        // GPIO_SetBits(GPIOA, GPIO_Pin_3);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_3);

        // GPIO_SetBits(GPIOA, GPIO_Pin_4);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_4);

        // GPIO_SetBits(GPIOA, GPIO_Pin_5);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_5);

        // GPIO_SetBits(GPIOA, GPIO_Pin_6);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_6);

        // GPIO_SetBits(GPIOA, GPIO_Pin_7);
        // GPIO_ResetBits(GPIOA, GPIO_Pin_7);

        if (hval > stop_max && vval > stop_min) {
            if (hval > vval) {
                dir = 0;
            } else {
                dir = 1;
            }
        }
        if (hval < stop_max && vval < stop_min) {
            if (hval < vval) {
                dir = 0;
            } else {
                dir = 1;
            }
        }
        if (dir == 0) {
            // // PWM
            if (hval > stop_max) {
                cv = 255 - hval;
                PWM_Right();
            } else if (hval < stop_min) {
                cv = hval;
                PWM_Left();
            }
            OLED_ShowString(56, 5, "H");
        }
        if (dir == 1) {
            if (vval > stop_max) {
                cv = 255 - vval;
                PWM_Back();
            } else if (vval < stop_min) {
                cv = vval;
                PWM_Go();
            }
            OLED_ShowString(56, 5, "V");
        }
        if (hval >= stop_min && hval <= stop_max && vval >= stop_min && vval <= stop_max) {
            hval = 0;
            vval = 0;
            cv   = 125;
            PWM_Stop();
            OLED_ShowString(0, 5, "STOP");
        }

        cv  = scalerCV.conv(&scalerCV, cv);
        ecv = scalerCV.conv(&scalerECV, cv) / 20;

        // cv = hval;
        TIM_SetCompare1(TIM3, ecv * ecv); // L298n左边怀了
        TIM_SetCompare2(TIM3, cv * cv);
        TIM_SetCompare3(TIM3, cv * cv);
        TIM_SetCompare4(TIM3, cv * cv);

        printf("%d\n", cv);
        OLED_ShowNum(0, 3, cv, 4, 20);
        // OLED_ShowNum(0, 5, ecv, 4, 20);
    }
    return 0;
}

static int receive_demo()
{
    PWM_Config(2);
    uint16_t v    = 0;
    uint8_t  step = 0;
    while (1) {
        // TIM_SetCompare2(TIM3, 125 * 125); // PB1
        delay_ms(20000);
        // TIM_SetCompare2(TIM3, 125 * 125); // PB1
        // GPIO_SetBits(GPIOB, GPIO_Pin_5);
        // TIM_SetCompare1(TIM3, 0); // PB4
        // TIM_SetCompare2(TIM3, 0); // PB5
        // TIM_SetCompare3(TIM3, 0); // PB0
        // TIM_SetCompare4(TIM3, 0); // PB1

        delay_ms(20000);
        v = 125 * 5 * step;
        TIM_SetCompare2(TIM3, v); // PB1

        // if (step == 0) {
        //     TIM_SetCompare2(TIM3, 0); // PB5
        //     step++;
        // } else if (step == 1) {
        //     TIM_SetCompare2(TIM3, 125 * 125 / 3); // PB5
        //     step++;
        // } else if (step == 2) {
        //     TIM_SetCompare2(TIM3, 125 * 125 / 2); // PB5
        //     step++;
        // } else if (step == 3) {
        //     TIM_SetCompare2(TIM3, 125 * 125); // PB1
        //     step = 0;
        // }
        step++;
        if (step > 25) step = 0;
        printf("%d\n", v);
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
    // WS2812B_Gradient();

    return send();
    // return send_demo();
    // return receive();
    // return receive_demo();
    // return WS2812B_Gradient();
}
