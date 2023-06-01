add_rules("mode.debug", "mode.release")



toolchain("arm-none-eabi", function()
  set_kind("standalone")
  set_toolset("cc", "arm-none-eabi-gcc")
  set_toolset("as", "arm-none-eabi-gcc")
  set_toolset("ld", "arm-none-eabi-gcc")
end)


task("flash", function()
  on_run(function()
    print("**********************以下开始写入stm32*******************")
    os.exec("JLinkExe -autoconnect 1 -device STM32F103C8 -if swd -speed 4000  -commandfile ./download.jlink")
    print("******************如果上面没有error,则写入成功********************")
  end)
end)

target("main", function()
  set_kind("binary")
  set_toolchains("arm-none-eabi")
  add_files(
    "main.c",
    "./startup_stm32f103xb.s",
    "./stm32f10x_gpio.c"
  )
  -- add_defines(
  --   "USE_HAL_DRIVER",
  --   "STM32F103xB"
  -- )
  add_cflags(
    "-Og",
    "-mcpu=cortex-m3",
    "-mthumb",
    "-Wall -fdata-sections -ffunction-sections",
    "-g -gdwarf-2", { force = true }
  )

  add_asflags(
    "-Og",
    "-mcpu=cortex-m3",
    "-mthumb",
    "-x assembler-with-cpp",
    "-Wall -fdata-sections -ffunction-sections",
    "-g -gdwarf-2", { force = true }
  )

  add_ldflags(
    "-Og",
    "-mcpu=cortex-m3",
    "-L./",
    "-TSTM32F103C8Tx_FLASH.ld",
    "-Wl,--gc-sections",
    "-lc -lm -lnosys -lrdimon -u _printf_float", { force = true }
  )

  set_targetdir("build")
  set_filename("output.elf")

  after_build(function(target)
    print("生成HEX 和BIN 文件")
    os.exec("arm-none-eabi-objcopy -O ihex ./build/output.elf ./build/output.hex")
    os.exec("arm-none-eabi-objcopy -O binary ./build/output.elf ./build/output.bin")
    print("生成已完成")
    import("core.project.task")
    task.run("flash")
    print("********************储存空间占用情况*****************************")
    os.exec("arm-none-eabi-size -Ax ./build/output.elf")
    os.exec("arm-none-eabi-size -Bx ./build/output.elf")
    os.exec("arm-none-eabi-size -Bd ./build/output.elf")
    print("heap-堆、stck-栈、.data-已初始化的变量全局/静态变量，bss-未初始化的data、.text-代码和常量")
  end)
end)
