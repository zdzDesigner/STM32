## gpio

- usart (重定向 printf)

```md
RCC_APB2Periph_GPIOA

GPIO_Pin_9
GPIO_Pin_10
```

- adc (采集遥控器数据)

```md
RCC_APB2Periph_GPIOA

GPIO_Pin_4
GPIO_Pin_5
```

- nrf24l01

```md
SPI2
RCC_APB2Periph_GPIOB

● MISO：主设备输入/从设备输出引脚。该引脚在从模式下发送数据，在主模式下接收数据。
● MOSI：主设备输出/从设备输入引脚。该引脚在主模式下发送数据，在从模式下接收数据。
● SCK：串口时钟，作为主设备的输出，从设备的输入
GPIO_Pin_13: SCK
GPIO_Pin_14: MISO
GPIO_Pin_15: MOSI

GPIO_Pin_10: IRQ
GPIO_Pin_11: CE
GPIO_Pin_12: CSN(NSS)
```
