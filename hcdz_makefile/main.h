#define PERIPH_BASE (unsigned int)0x40000000 // 总线基地址
#define APB1PERIPH_BASE PERIPH_BASE // APB1基地址
#define APB2PERIPH_BASE (PERIPH_BASE+0x00010000) // APB2基地址
#define AHBPERIPH_BASE (PERIPH_BASE+0x00020000) // AHB基地址 实际是:0x00018000





// 32位结构体的特性,key占用4个byte(字节),下一个名字会自动偏移0x04,和stm32文档中的偏移地址一致
typedef unsigned int unit32_t;
typedef struct {
    unit32_t CRL;
    unit32_t CRH;
    unit32_t IDR;
    unit32_t ODR;
    unit32_t BSRR;
    unit32_t BRR;
    unit32_t LOCK;
} GPIO_TypeDef;
#define GPIOC_BASE (APB2PERIPH_BASE+0x00001000) // GPIOC 基地址
#define GPIOC ((GPIO_TypeDef*)GPIOC_BASE)


typedef struct {
    unit32_t CR;
    unit32_t CFGR;
    unit32_t CIR;
    unit32_t APB2RSTR;
    unit32_t APB1RSTR;
    unit32_t AHBENR;
    unit32_t APB2ENR;
    unit32_t APB1ENR;
    unit32_t BDCR;
    unit32_t CSR;
} RCC_TypeDef;

#define RCC_BASE (AHBPERIPH_BASE+0x1000) // 时钟基地址
#define RCC ((RCC_TypeDef*)RCC_BASE)


