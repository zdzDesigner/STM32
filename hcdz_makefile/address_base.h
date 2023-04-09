#define PERIPH_BASE (unsigned int)0x40000000 // 总线基地址
#define APB1PERIPH_BASE PERIPH_BASE // APB1基地址
#define APB2PERIPH_BASE (PERIPH_BASE+0x00010000) // APB2基地址
#define AHBPERIPH_BASE (PERIPH_BASE+0x00020000) // AHB基地址 实际是:0x00018000

#define GPIOC_BASE (APB2PERIPH_BASE+0x00001000) // GPIOC 基地址
#define GPIOC_CRH *(unsigned int*)(GPIOC_BASE+0x04) // 输出模式 0x40011004 = GPIOC_BASE+0x00000004
#define GPIOC_IDR *(unsigned int*)(GPIOC_BASE+0x08) // 配置输入基地址 0x40011008
#define GPIOC_ODR *(unsigned int*)(GPIOC_BASE+0x0C) // 配置输出基地址 0x4001100C


#define RCC_BASE (AHBPERIPH_BASE+0x1000) // 时钟基地址
#define RCC_APB2ENR *(unsigned int*)(RCC_BASE + 0x18) // GPIOC时钟 0x40021018
