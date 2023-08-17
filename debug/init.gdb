set remotetimeout 100
target extended-remote :3333
file ./build/output.elf

# set remote hardware-watchpoint-limit 2
mon reset halt
maintenance flush register-cache
# flushregs
break main
# load
# run
c
