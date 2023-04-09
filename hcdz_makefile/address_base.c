
void addressBase(){
    RCC_APB2ENR |=(1<<4); // 打开GPIOC时钟
    GPIOC_CRH &=~(0x0F<<(4*5)); // 配置输出模式, 偏移地址
    GPIOC_CRH |=(1<<(4*5));
    GPIOC_ODR &=~(1<<13); // 配置输出低电平
    // GPIOC_ODR |=(1<<13); // 配置输出高电平
    while(1);    
}