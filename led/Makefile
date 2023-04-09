TARGET=test
BUILD_DIR = build
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
RM=rm -f
CORE=3
CPUFLAGS=-mthumb -mcpu=cortex-m$(CORE)
AS = arm-none-eabi-gcc -x assembler-with-cpp
HEX = $(OBJCOPY) -O ihex
BIN = $(OBJCOPY) -O binary -S


# # C defines -D
C_DEFS =  \
-DSTM32F10X_MD \
-DUSE_STDPERIPH_DRIVER

# C sources
C_SOURCES =  \
main.c \
# stm32f10x_gpio.c \

# 引导文件
LDFLAGS = -T STM32F103C8Tx_FLASH.ld -Wl,-cref,-u,Reset_Handler -Wl,-Map=$(TARGET).map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group
CFLAGS=-g -o
# CFLAGS= $(C_DEFS) -g -o 


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/$(TARGET).elf:$(BUILD_DIR)/startup_stm32f103xb.o $(BUILD_DIR)/main.o $(BUILD_DIR)/stm32f10x_gpio.o
	$(CC) $^ $(CPUFLAGS) $(LDFLAGS) $(CFLAGS) $@

# $(BUILD_DIR)/startup_stm32f103xb.o:startup_stm32f103xb.s
# 	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@
$(BUILD_DIR)/startup_stm32f103xb.o:startup_stm32f103xb.s
	$(AS) -c  $< -Og  -o $@

$(BUILD_DIR)/main.o:main.c
	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@

$(BUILD_DIR)/stm32f10x_gpio.o:stm32f10x_gpio.c
	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@


# bin:$(TARGET).elf
# 	$(OBJCOPY) $^  -O binary -S $(TARGET).bin

# hex:$(TARGET).elf
# 	$(OBJCOPY) $^ -O ihex $(TARGET).hex




$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		


down:$(BUILD_DIR)/$(TARGET).bin
	JLinkExe -autoconnect 1 -device STM32F103C8 -if swd -speed 4000  -commandfile ./download.jlink


clean:
	$(RM) $(BUILD_DIR)/*


# clean:
# 	$(RM) *.o $(TARGET).*

# run:stm32f10x_gpio.c main.c
# 	gcc $^ -o $@ && ./$@
