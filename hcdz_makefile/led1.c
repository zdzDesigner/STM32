
void led1(){
    *(unsigned int*)0x40021018 |=(1<<4); // 打开GPIOC时钟
    *(unsigned int*)0x40011004 &=~(0x0F<<(4*5)); // 配置输出模式
    *(unsigned int*)0x40011004 |=(1<<(4*5));
    *(unsigned int*)0x4001100C &=~(1<<13); // 配置输出低电平
    // *(unsigned int*)0x4001100C |=(1<<13); // 配置输出高电平
    while(1);
    
}
