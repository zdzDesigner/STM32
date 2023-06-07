add_rules("mode.debug", "mode.release")
toolchain("arm-none-eabi", function()
  set_kind("standalone")
  set_toolset("cc", "arm-none-eabi-gcc")
  set_toolset("as", "arm-none-eabi-gcc")
  set_toolset("ld", "arm-none-eabi-gcc")
end)
target("stm32", function()
  set_kind("binary")
  set_toolchains("arm-none-eabi")

  add_files(
    "./src/**.c",
    "./sys/**.c",
    "./lib/CMSIS/system_stm32f10x.c",
    "./lib/STM32F10x_StdPeriph_Driver/src/*.c",
    "./startup_stm32f103xb.s"
  )
  add_includedirs(
    "./src",
    "./src/key",
    "./src/led",
    "./sys",
    "./sys/oledv2",
    "./sys/util",
    "./sys/sr04",
    "./sys/debug",
    "./sys/nrf24",
    "./lib/CMSIS",
    "./lib/STM32F10x_StdPeriph_Driver/inc"
  )
  -- ./prj/MDK-ARM/PRESSURE_CONTROL_PY_V1.uvprojx
  -- PY32F002Ax5,USE_FULL_LL_DRIVER,USE_HAL_DRIVER
  add_defines(
    "STM32F10X_LD",
    "USE_STDPERIPH_DRIVER"
  )
  add_cflags(
    "-Og",
    "-mthumb",
    -- "-mcpu=cortex-m0",
    "-mcpu=cortex-m3",
    "-Wall -fdata-sections -ffunction-sections",
    "-g -gdwarf-2", { force = true }
  )
  add_asflags(
    "-Og",
    "-mthumb",
    -- "-mcpu=cortex-m0",
    "-mcpu=cortex-m0plus",
    "-x assembler-with-cpp",
    "-Wall -fdata-sections -ffunction-sections",
    "-g -gdwarf-2", { force = true }
  )
  add_ldflags(
    -- "-Og",
    "-mthumb",
    -- "-mcpu=cortex-m0",
    "-mcpu=cortex-m3",
    -- "-L./",
    "-TSTM32F103C8Tx_FLASH.ld",
    "-Wl,--gc-sections",
    "-Wl,--print-memory-usage",
    "-specs=nano.specs",
    -- "-specs=nosys.specs",
    "-lc -lm -lnosys",
    -- "-lc -lm -lnosys -lrdimon -u _printf_float",
    { force = true }
  )
  set_targetdir("build")
  set_filename("output.elf")
  after_build(function(target)
    print("生成HEX 和BIN 文件")
    os.exec("arm-none-eabi-objcopy -O ihex ./build//output.elf ./build//output.hex")
    os.exec("arm-none-eabi-objcopy -O binary ./build//output.elf ./build//output.bin")
    print("生成已完成")
    import("core.project.task")
    -- task.run("flash")
    print("********************储存空间占用情况*****************************")
    os.exec("arm-none-eabi-size -Ax ./build/output.elf")
    os.exec("arm-none-eabi-size -Bx ./build/output.elf")
    os.exec("arm-none-eabi-size -Bd ./build/output.elf")
    print("heap-堆、stck-栈、.data-已初始化的变量全局/静态变量，bss-未初始化的data、.text-代码和常量")
  end)
end)
-- arm-none-eabi-gcc -x assembler-with-cpp -c -mcpu=cortex-m3 -mthumb   -DSTM32F10X_LD -DUSE_STDPERIPH_DRIVER -Ilib/CMSIS -Ilib/STM32F10x_StdPeriph_Driver/inc -I./sys  -I./sys/sr04  -I./sys/debug  -I./sys/util  -I./sys/nrf24  -I./sys/oledv2  -I./src  -I./src/key  -I./src/bns  -I./src/demo  -I./src/led  -Og -fdata-sections -ffunction-sections -g -O0 -gdwarf-2 -MMD -MP -MF"build/startup_stm32f103xb.d" -MT"build/startup_stm32f103xb.d" startup_stm32f103xb.s -o build/startup_stm32f103xb.o
-- arm-none-eabi-gcc
--   build/system_stm32f10x.o
--   build/stm32f10x_gpio.o
--   build/stm32f10x_tim.o
--   build/stm32f10x_adc.o
--   build/stm32f10x_dma.o
--   build/stm32f10x_dac.o
--   build/stm32f10x_spi.o
--   build/stm32f10x_rcc.o
--   build/stm32f10x_usart.o
--   build/misc.o
--   build/stm32f10x_i2c.o
--   build/stm32f10x_exti.o
--   build/sr04.o
--   build/debug.o
--   build/usart2.o build/avg.o
--   build/scale.o build/util.o build/i2c.o build/nrf24.o build/exti.o build/spi_single.o build/usart.o
--   build/dma.o build/delay.o build/time2.o build/wifi.o build/pwm.o build/printf.o build/tool.o
--   build/dac.o build/spi.o build/adc.o build/spi_duplex.o build/oled.o build/key.o build/stm32f10x_it.o
--   build/main.o build/led2.o build/led.o build/startup_stm32f103xb.o
--   -mcpu=cortex-m3 -mthumb   -specs=nano.specs -TSTM32F103C8Tx_FLASH.ld  
--   -lc -lm -lnosys  
--   -Wl,-Map=build/target.map,--cref -Wl,--gc-sections -o build/target.elf
--
--
-- arm-none-eabi-gcc
--   -o build/output.elf
--   -s -Og -mthumb -mcpu=cortex-m3 -L./ -TSTM32F103C8Tx_FLASH.ld -Wl,
--   --gc-sections -Wl,--print-memory-usage -specs=nano.specs -specs=nosys.specs -lc -lm -lnosys
--   build/.objs/stm32/linux/x86_64/release/startup_stm32f103xb.s.o
--   build/.objs/stm32/linux/x86_64/release/src/key/key.c.o
--   build/.objs/stm32/linux/x86_64/release/src/stm32f10x_it.c.o
--   build/.objs/stm32/linux/x86_64/release/src/main.c.o
--   build/.objs/stm32/linux/x86_64/release/src/led/led2.c.o
--   build/.objs/stm32/linux/x86_64/release/src/led/led.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/sr04/sr04.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/debug/debug.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/usart2.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/util/avg.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/util/scale.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/util/util.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/i2c.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/nrf24/nrf24.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/exti.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/spi_single.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/usart.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/dma.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/delay.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/time2.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/wifi.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/pwm.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/printf.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/tool.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/dac.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/spi.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/adc.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/spi_duplex.c.o
--   build/.objs/stm32/linux/x86_64/release/sys/oledv2/oled.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/misc.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c.o
--   build/.objs/stm32/linux/x86_64/release/lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c.o
--
