set remotetimeout 100
target extended-remote :3333
file ./build/output.elf


# source /home/zdz/Documents/Try/IOT/STM32/course/debug/.gdbinit
# set remote hardware-watchpoint-limit 2
mon reset halt
maintenance flush register-cache
# flushregs
break main
break src/ws2812b/ws2812b.c:13
# load
# run
c

## 自定义命令 ==================
define ctitle
  echo hello\n
end

define cargs
  echo arguments.length:$argc\n
  echo $arg0\n
  echo $arg1\n
end


set $ADDRESS = 0
define db
  if $argc < 1
    printf "address not found!\n"
    return
  end
  printf $_

  set $count = 16
  if $ADDRESS != 0 
    set $ADDRESS += $count
  else
    set $ADDRESS = $arg0
  end

  if $count == 8
    x /8bx $ADDRESS
  end
  if $count == 16
    x /16bx $ADDRESS
  end
  if $count == 32
    x /32bx $ADDRESS
  end
end
document db
same as pwngdb.
end


define cp
    if !$_
        printf "No previous command\n"
    else
      if $_ == $_
        printf "Repeating the same command\n"
      else
        printf "Different command\n"
      end
    end
end






