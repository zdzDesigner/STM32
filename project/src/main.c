#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sys.h"
// uint32_t count = 0;
extern uint16_t ADC_VAL[2];

int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    delay_init();
    // delay_init_stk();
    PRINT_Config();

    // WIFI_USART_Start();
    // WIFI_Esp8266();

    OLED_Init();
    /* OLED_Clear(); */

    // OLED_ShowCHinese(30, 0, 0);
    // OLED_ShowCHinese(48, 0, 1);
    // OLED_ShowCHinese(66, 0, 2);
    // OLED_ShowCHinese(84, 0, 3);
    /* OLED_ShowString(0, 3, "0.96' OLED TEST"); */
    // OLED_ShowString(8, 2, "ZHONGJINGYUAN");
    // // //	OLED_ShowString(20,4,"2014/05/01");
    // OLED_ShowString(0, 6, "ASCIIzdzzzz:");
    // OLED_ShowString(63, 6, "CODE:");

    /* 接收模式 */
    // OLED_Clear();
    // OLED_ShowNum(0, 0, 100, 4, 20);

    // CHECK_SPI_Config();
    // CHECK_SPI_SINGLE_Config();
    // SPI_Config();

    // SR04_Config();

    // while (1) {
    //     /* code */
    // }
    // return 0;

    // /*SPI 24l01初始化*/
    /* extern uint8_t TX_BUF[TX_PLOAD_WIDTH]; */
    /* extern uint8_t RX_BUF[RX_PLOAD_WIDTH]; */
    SPI_NRF_Init();
    /* delay_ms(100); */

    /*检测NRF模块与MCU的连接*/

    /* printf("NRF_READ_REG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG)); */
    /* printf("CONFIG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + CONFIG)); */
    /* printf("STATUS:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + STATUS)); */
    /* uint8_t status = NRF_Check(); */
    /* printf("%d\n", status); */
    /* OLED_Clear(); */
    /* OLED_ShowString(0, 0, "status:"); */
    /* OLED_ShowNum(56, 0, status, 1, 20); */
    /* while (status != SUCCESS) { */
    /*     printf("\r\n NRF与MCU连接失败，请重新检查接线！\r\n"); */
    /* } */
    /* OLED_ShowString(0, 2, "nrf to mcu ok"); */
    /* printf("\r\n NRF与MCU连接成功\r\n"); */

    /* 进入接收模式 */
    NRF_RX_Mode();     // NRF 进入接收模式 
    /* uint8_t hval = 0;  // digital */
    /* uint8_t cv   = 20; */
    /* PWM_Config(); */
    /* while (1) { */
    /*     NRF_Rx_Dat(RX_BUF); */
    /*     uint8_t hval = RX_BUF[0]; */
    /*     uint8_t vval = RX_BUF[1]; */
    /*     printf("%d,%d\n", hval, vval); */
    /*     OLED_Clear(); */
    /*     OLED_ShowNum(0, 0, hval, 5, 20); */
    /*     OLED_ShowNum(56, 0, vval, 4, 20); */
    /*  */
    /*     if (hval > 125) { */
    /*         if (hval > 240) { */
    /*             cv = 0; */
    /*         } else { */
    /*             cv = 240 - hval; */
    /*         } */
    /*         PWM_Back(); */
    /*     } else if (hval < 105) { */
    /*         cv = hval; */
    /*         PWM_Go(); */
    /*     } else if (vval > 105 && vval < 125) { */
    /*         PWM_Stop(); */
    /*     } */
    /*  */
    /*     if (vval > 155) { */
    /*         printf("vval:%d\n", vval); */
    /*         if (vval > 240) { */
    /*             cv = 20; */
    /*         } else { */
    /*             cv = (240 - vval)+20; */
    /*         } */
    /*         PWM_Right(); */
    /*     } else if (vval < 65) { */
    /*         cv = vval+20; */
    /*         PWM_Left(); */
    /*     } */
    /*     // printf("GPIO_Pin_2:%d\n", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0)); */
    /*     // printf("GPIO_Pin_3:%d\n", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)); */
    /*  */
    /*  */
    /*     TIM_SetCompare1(TIM3, cv * cv); */
    /*     TIM_SetCompare2(TIM3, cv * cv); */
    /*     TIM_SetCompare3(TIM3, cv * cv); */
    /*     TIM_SetCompare4(TIM3, cv * cv); */
    /* } */
    /* return 0; */

    /* 进入发送模式 */
    // ADC_Config();
    // Scaler scaler = ScalerInit(0, 255, 1740, 2400);
    // printf("%s\n", "adc send start");
    // NRF_TX_Mode();
    // delay_ms(100);
    //
    // u16 hval = 0;
    // u16 vval = 0;
    // while (1) {
    //     delay_ms(10);
    //     /* 发送模式 */
    //     hval = scaler.conv(&scaler, ADC_VAL[0]);
    //     vval = scaler.conv(&scaler, ADC_VAL[1]);
    //
    //     printf("hval:%d,vval:%d\n", hval, vval);
    //     // TX_BUF[0] = (uint8_t)hval;
    //     // TX_BUF[1] = (uint8_t)vval;
    //     // NRF_Tx_Dat(TX_BUF);
    //     // uint8_t NrfStatus = NRF_Tx_Dat(TX_BUF);
    //     // printf("%s\n", "send ");
    //     // printf("send after status:%d\n", NrfStatus);
    // }
    // return 0;

    // printf("%s\n", "send start");
    // delay_ms(1000);
    // NRF_TX_Mode();
    // uint8_t count = 0;
    // while (1) {
    //     delay_ms(1000);
    //     /* 发送模式 */

    //     TX_BUF[0] = count++;
    //     TX_BUF[1] = 2;
    //     TX_BUF[2] = 3;
    //     // printf("NRF_READ_REG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG));
    //     // printf("CONFIG:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + CONFIG));
    //     // printf("STATUS:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + STATUS));
    //     // printf("FIFO_STATUS:%d\n", SPI_NRF_ReadReg(NRF_READ_REG + NRF_FIFO_STATUS));
    //     uint8_t NrfStatus = NRF_Tx_Dat(TX_BUF);
    //     printf("%s\n", "send ");
    //     printf("send after status:%d\n", NrfStatus);

    //     // NRF_Rx_Dat(RX_BUF);
    //     /* 发送数据的状态 */
    //     // if (NrfStatus == TX_DS) {
    //     //     printf("\r\n发送数据成功\r\n");
    //     // } else {
    //     //     printf("\r\n发送数据失败 %d\r\n", NrfStatus);
    //     // }
    // }

    NRF24_Config();

    // USART_DMA_Demo
    // while (1) {
    //     /* code */
    // }

    // DMA_M2M_Demo();

    ADC_Config();
    /* PWM_Config(); */
    u16 ch4 = 0;
    u16 ch5 = 0;
    Scaler scaler = ScalerInit(0, 18000, 1740, 2400);
    /* Scaler scaler = ScalerInit(0, 18000, 0, 4095); */
    while (1) {
        delay_ms(30);
        // delay_ms_stk(1000);
        // count++;
        // printf("%ld\n",count);
        /* val = ADC_AVG_Read(1000); */
        ch4 = ADC_AVG_ReadCh(ADC_Channel_4, 1000);
        ch4 = scaler.conv(&scaler, ch4);
        ch5 = ADC_AVG_ReadCh(ADC_Channel_5, 1000);
        ch5 = scaler.conv(&scaler, ch5);
        printf("--%d, %d\n", ch4, ch5);
        // printf("--\n");

        // TIM_SetCompare1(TIM3, 0);
        /* TIM_SetCompare1(TIM3, val); */
        /* TIM_SetCompare2(TIM3, val); */
        // TIM_SetCompare2(TIM3, 0);
        // TIM_SetCompare2(TIM3, 10);
        // TIM_SetCompare2(TIM3, 100);
        // TIM_SetCompare2(TIM3, 500);
        // TIM_SetCompare2(TIM3, 1000);
        // TIM_SetCompare2(TIM3, 2000);
        // TIM_SetCompare2(TIM3, 10000);
    }
    return 0;

    ADC_Config();
    while (1) {
        delay_ms(30);
        // printf("\nesp8366 demo ===========x==\n");
        // printf("gpio:%d\n", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
        // printf("%d\n", ADC_Read(ADC_Channel_4));
        /* printf("4::%d\n", ADC_AVG_Read(ADC_Channel_4, 100)); */
        printf("5::%d\n", ADC_AVG_Read(100));
        // OLED_Clear();
        // OLED_ShowNum(0, 6, ADC_Read(ADC_Channel_4), 2, 20);
        // OLED_ShowNum(0, 6, ADC_AVG_Read(ADC_Channel_4, 10), 2, 20);
    }
    return 0;

    // PWM_Config();
    // // TIM_SetCompare1(TIM3, (1 << 16) - 1);
    // // TIM_SetCompare2(TIM3, (1 << 16) - 1);
    // // TIM_SetCompare3(TIM3, (1 << 16) - 1);
    // TIM_SetCompare1(TIM3, 0);
    // TIM_SetCompare2(TIM3, 0);
    // TIM_SetCompare3(TIM3, 0);
    // // u16 redval = 0;
    // // u8 dir     = 1;
    // while (1) {
    //     // delay_ms(30);
    //     // if (dir) {
    //     //     redval++;
    //     // } else {
    //     //     redval--;
    //     // }
    //     // if (redval >= 16) dir = 0;
    //     // if (redval == 0) dir = 1;
    //     // TIM_SetCompare1(TIM3, (1 << redval)-1);
    //     // TIM_SetCompare2(TIM3, (1 << redval)-1);
    //     // TIM_SetCompare3(TIM3, (1 << redval)-1);
    //     // // OLED_ShowTest(0,6,)
    //     // // OLED_Clear();
    //     // // OLED_ShowNum(0, 6, redval, 2, 20);
    // }

    // u16 led0pwmval = 0;
    // u8 dir         = 1;
    // while (1) {
    // // delay_ms(1);
    // delay_us(50);
    // // delay_us(100);
    // if (dir) {
    //     led0pwmval++;
    // } else {
    //     led0pwmval--;
    // }
    // if (led0pwmval > 25600) dir = 0;
    // if (led0pwmval == 0) dir = 1;
    // TIM_SetCompare1(TIM4, 0);
    // TIM_SetCompare2(TIM4, 0);
    // TIM_SetCompare3(TIM4, 0);
    // TIM_SetCompare2(TIM4,0);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,300);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,400);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,800);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,1600);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,3200);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,6400);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,12800);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,25600);
    // delay_ms(1000);
    // TIM_SetCompare2(TIM4,45600);
    // delay_ms(1000);
    // }

    // DAC_Config();
    // while (1) {
    //     u_int8_t i = 0;
    //     for (; i < 10; i++) {
    //         char dstr[20];
    //         uint16_t d = i * 500;
    //         if (d > 0x01 << 12) {
    //             d = (0x01 << 12)-1;
    //         }
    //         sprintf(dstr, "%d", d);  //将d 保留2位小数赋值给dstr
    //         DAC_SetChannel1Data(DAC_Align_12b_R, d);
    //         OLED_Clear();
    //         OLED_ShowString(0, 6, dstr);
    //         // OLED_ShowNum(0, 4, i * 400, 4, 1);
    //         delay_ms(1000);
    //     }
    // }

    // USART_SendString(USART3, "wifi 通信");

    // USART_SendString(USART3, "WIFI_RX_STA RESET");
    // WIFI_RX_STA = 0;

    // WIFI_IIM_Start(9000, 7200);

    // USART2_Start();
    // USART_SendString(USART2, "usart2");

    // SendByte('z');
    // SendByte('d');
    // SendByte('z');
    // USART_SendString(USART1, "zdzlmy");
    // USART_SendString(USART1, "他哦啊麻栗坡美国xxx");
    // LED_GPIO_Config();
    // MY_EXTI_Config();
    // TIME3_Init(10000, 7200);
    // char ch2[3];
    // printf("str:%s\n", itoa(201, ch2, 10));
    // printf( "天气不错天气不错天气不错天气不错天气不错天气不错天气不错天 \ 气不错天气不错天气不错天气不错%d/%s\n", 7, "dd");

    // LED_Open();
    // printf("天气不错%d/%s",7,"dd");
    // fflush(stdout);
    // printx("天气不错%d/%s",7,"dd");
    // uint8_t temp;
    // while (1) {
    // delay_ms_stk(5000);
    // printf("天气不错%d/%s\n",7,"dd");
    // if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
    //     char ch3[3];
    //     temp = (uint8_t)USART_ReceiveData(USART1);
    //     USART_SendString(USART1, itoa(temp, ch3, 10));
    //     // USART_SendString(USART1,itoa(temp,10));

    //     // SendByte(temp);
    //     SendByte('\n');
    // }

    // if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
    //     temp = (uint8_t)USART_ReceiveData(USART3);
    //     USART_SendByte(USART3, temp);
    // }

    // if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET) {
    //     temp = (uint8_t)USART_ReceiveData(USART2);
    //     USART_SendByte(USART2, temp);
    // }

    // if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
    //     temp = (uint8_t)USART_ReceiveData(USART1);
    //     USART_SendByte(USART1, temp);
    // }

    // if (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET) {
    //     USART_SendString(USART1, "--TIM_FLAG--");
    //     TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    // }
    // }

    /* 中断 NVIC */
    // LED1_GPIO_Config();

    // LED_GPIO_Config();
    // KEY_GPIO_Config();
    // while (1) {
    //     if (KEY_DOWN) {
    //         LED_Open();
    //     } else {
    //         LED_Close();
    //     }

    //     // PDout(2) = 1;
    //     // delay_ms_stk(200);
    //     // PDout(2) = 0;
    //     // delay_ms_stk(100);
    // }

    /* key check */
    // LED_GPIO_Config();
    // KEY_GPIO_Config();

    // while (1) {
    //     if (KEY_DOWN) {
    //         // delay_ms_stk(1000);
    //         LED_Open();
    //     } else {
    //         LED_Close();
    //         // delay_ms_stk(1000);

    //     }
    //     count++;
    // }

    /* delay */
    // LED_GPIO_Config();
    // while (1)
    // {
    //     printf("%s\n","open");
    //     LED_Open();
    //     printf("GPIOB Pin_4:%d\n",GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4));
    //     delay_ms(1000);
    //     printf("%s\n","close");
    //     LED_Close();
    //     printf("GPIOB Pin_4:%d\n",GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4));
    //     delay_ms(1000);
    // }
}
