#include <string.h>
#include "stm32f10x_rcc.h"
#include "ws2812b.h"

#define LIGHT_LEN      1
#define LIGHT_BYTE_LEN LIGHT_LEN * 24
#define DMA_CHANNEL    DMA1_Channel2 // 映射 TIM2_UP , 对所有TIM2映射的GPIO都有效
#define DMA_FLAG_TC    DMA1_FLAG_TC2

uint16_t LED_Buffer[LIGHT_BYTE_LEN]; // 12个灯*24位=288位数据

void WS2812B_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开GPIOA启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 开TIM2启时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    // 开DMA1启时钟

    // PA0->DI
    GPIO_InitTypeDef GPIO_InitStructure;
    // GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    // GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period        = 90 - 1; // 800kHz  ARR
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;      // psc
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        // PWM1模式，小于比较值输出高电平，大于输出低电平，
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 开启输出通道引脚
    TIM_OCInitStructure.TIM_Pulse       = 0;                      // 比较值初始为0，一直输出低电平
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    // TIM_OC1Init(TIM2, &TIM_OCInitStructure); // TIM2_CH1 使能通道1
    // TIM_OC2Init(TIM2, &TIM_OCInitStructure); // TIM2_CH2 使能通道2
    TIM_OC4Init(TIM2, &TIM_OCInitStructure); // TIM2_CH4 使能通道4

    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA_CHANNEL);
    // DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (TIM2->CCR1); // 外设站点起始地址
    // DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (TIM2->CCR2);       // 外设站点起始地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (TIM2->CCR4);       // 外设站点起始地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 数据宽度
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;       // 是否自增
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)LED_Buffer;            // 存储器站点的起始地址
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;     // 数据宽度
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;            // 是否自增
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;           // 传输方向，从存储器到外设
    DMA_InitStructure.DMA_BufferSize         = 0;                               // 缓存区大小，传输计数器
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;                 // 传送模式，单次循环
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                 // 存储器到存储器
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;               // 优先级
    DMA_Init(DMA_CHANNEL, &DMA_InitStructure);                                  // DMA1通道

    TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE); // 使能定时器2的TIM_DMA_Update更新中断
    // TIM_DMACmd(TIM2, TIM_DMA_CC1, ENABLE); // 只对TIM2_CH1 有效
    // TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE); // 只对TIM2_CH2 有效
}

void WS2812B_send(uint32_t GRB_Data) // 发送颜色数据 0X 00 00 00
{
    uint16_t i, j, z = 0;

    for (j = 0; j < LIGHT_LEN; j++) {
        for (i = 0; i < 24; i++) {
            if (0x800000 & ((GRB_Data << i))) // 比较每一位的值，是0码还是1码
            {
                LED_Buffer[z] = 55; // 1
            } else {
                LED_Buffer[z] = 25; // 0
            }
            z++;
        }
    }

    DMA_SetCurrDataCounter(DMA_CHANNEL, LIGHT_BYTE_LEN); // 给传输计数器写数据，需要传送多少个数据
    DMA_Cmd(DMA_CHANNEL, ENABLE);                        // 使能DMA，开始传输
    TIM_Cmd(TIM2, ENABLE);                               // 使能定时器

    printf("xxxxxxx\n");
    while (!DMA_GetFlagStatus(DMA_FLAG_TC)) {} // 等待传输完成
    printf("xxxxxxx end\n");
    TIM_Cmd(TIM2, DISABLE);
    DMA_Cmd(DMA_CHANNEL, DISABLE); // 关闭DMA
    DMA_ClearFlag(DMA_FLAG_TC);    // 清除DMA标志位
}

void WS2812B_OFF(void)
{
    WS2812B_send(0X000000);
}

void WS2812B_ON(void)
{
    uint8_t step  = 0;
    char   *color = "blue";
    // red ==========
    if (0 == strcmp(color, "red")) {
        while (1) {
            WS2812B_send(step << 8);
            delay_ms(50);
            step++;
            if (step > 0xFF00) step = 0;
        }
    }

    // blue ==========
    if (0 == strcmp(color , "blue")) {
        while (1) {
            WS2812B_send(step);
            delay_ms(50);
            step++;
            if (step > 0xFF) step = 0;
        }
    }

    // green ==========
    while (1) {
        WS2812B_send(step << 16);
        delay_ms(50);
        step++;
        if (step > 0xFF0000) step = 0;
    }
}

// delay_ms(50);
// WS2812B_send(0X00AA00);
// delay_ms(50);
// WS2812B_send(0X00FF00);
// delay_ms(50);

// WS2812B_send(0X7FFF00);
// delay_ms(50);

// WS2812B_send(0XFFFF00);
// delay_ms(50);

// WS2812B_send(0XFF0000);
// delay_ms(50);

// WS2812B_send(0XFF00FF);
// delay_ms(50);

// WS2812B_send(0X0000FF);
// delay_ms(50);

// WS2812B_send(0X008BFF);
// delay_ms(50);

// WS2812B_send(0XFFFFFF);
// delay_ms(50);

// WS2812B_send(0X000000);
// delay_ms(50);
