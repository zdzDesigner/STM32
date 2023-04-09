# PC13
## 地址 0x40011000 ~ 0x400113FF
## 共7个寄存器 3FF
## 4*8*7 

# 寄存器 模型
## MODE[0,0] 两个字节
>> 00 输入模式 | 输出模式 :01=>10MHz,10=>2MHz,11=>50MHz
## CNF[0,0] 两个字节


# 0x0F<<(4*5)
## 0x0F => 1111 ,左移1 => 11110
## 0x0F<<(4*5) => 111100000000000000000000
## ~(0x0F<<(4*5)) 取反 => 000011111111111111111111

# & 符号 ， 常用作至0 操作
## 0 &任何数都是 0

## hex 文件小
-rw-rw-r-- 1 zdz zdz  312 5月  29 08:42 main.c
-rw-rw-r-- 1 zdz zdz 2.2K 5月  30 19:27 main.o
-rw-rw-r-- 1 zdz zdz  685 5月  30 19:27 Makefile
-rw-rw-r-- 1 zdz zdz 5.1K 5月  30 19:27 startup_stm32f103xb.o
-rw-rw-r-- 1 zdz zdz  10K 5月  28 22:43 startup_stm32f103xb.s
-rw-rw-r-- 1 zdz zdz 5.8K 5月  28 22:43 STM32F103C8Tx_FLASH.ld
-rwxrwxr-x 1 zdz zdz 137K 5月  30 19:27 test.bin
-rwxrwxr-x 1 zdz zdz 137K 5月  30 19:27 test.elf
-rw-rw-r-- 1 zdz zdz 5.3K 5月  30 20:22 test.hex
-rw-rw-r-- 1 zdz zdz  57K 5月  30 19:27 test.map

