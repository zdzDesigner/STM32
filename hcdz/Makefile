###################################### 文件
# TARGET=target
TARGET=output
BUILD_DIR=build

###################################### 编译器
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

###################################### 编译参数
CORE=3  # 级别
CPUFLAGS=-mthumb -mcpu=cortex-m$(CORE)

# ld
LDFLAGS = -T STM32F103C8Tx_FLASH.ld -Wl,-cref,-u,Reset_Handler -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group

CFLAGS=-Og -o

######################################
# C文件
C_SOURCES =  \
main.c 

C_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
# vpath %.c $(sort $(dir $(C_SOURCES)))

# 汇编文件
ASM_SOURCES =  \
startup_stm32f103xb.s

ASM_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
# vpath %.s $(sort $(dir $(ASM_SOURCES)))

######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


$(BUILD_DIR)/$(TARGET).elf:$(C_OBJECTS) $(ASM_OBJECTS)
	$(CC) $^ $(CPUFLAGS) $(LDFLAGS) $(CFLAGS) $@


$(BUILD_DIR)/%.o:%.s | $(BUILD_DIR) 
	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@

$(BUILD_DIR)/%.o:%.c | $(BUILD_DIR) 
	$(CC) -c $^ $(CPUFLAGS) $(CFLAGS) $@


 

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O ihex $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary -S $< $@	
	
$(BUILD_DIR):
	mkdir $@

down:$(BUILD_DIR)/$(TARGET).bin
	JLinkExe -autoconnect 1 -device STM32F103C8 -if swd -speed 4000  -commandfile ./download.jlink


clean:
	-rm -fR $(BUILD_DIR)


echo:
	echo $(ASM_OBJECTS)
	echo $(C_OBJECTS) $(ASM_OBJECTS)
# OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
