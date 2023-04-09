TARGET=test
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
AS = arm-none-eabi-gcc -x assembler-with-cpp
RM=rm -f
CORE=3
CPUFLAGS=-mthumb -mcpu=cortex-m$(CORE)
LDFLAGS = -T STM32F103C8Tx_FLASH.ld -Wl,-cref,-u,Reset_Handler -Wl,-Map=$(TARGET).map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group
HEX = $(OBJCOPY) -O ihex
BIN = $(OBJCOPY) -O binary
# BIN = $(OBJCOPY) -O binary -S


CFLAGS=-g -o

$(TARGET):startup_stm32f103xb.o main.o
	$(CC) $^ $(CPUFLAGS) $(LDFLAGS) $(CFLAGS) $(TARGET).elf

# startup_stm32f103xb.o:startup_stm32f103xb.s
# 	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@
startup_stm32f103xb.o:startup_stm32f103xb.s
	$(AS) -c  $< -Og  -o $@
	# $(AS) -c $^  $(CFLAGS) $@

main.o:main.c
	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@
 
bin:$(TARGET)
	$(BIN) $(TARGET).elf $(TARGET).bin

hex:$(TARGET)
	$(OBJCOPY) $(TARGET).elf -Oihex $(TARGET).hex

down:bin
	JLinkExe -autoconnect 1 -device STM32F103C8 -if swd -speed 4000  -commandfile ./download.jlink

clean:
	$(RM) *.o $(TARGET).*
