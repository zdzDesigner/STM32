main:
        push    {r7}
        sub     sp, sp, #12
        add     r7, sp, #0
        movw    r3, #4120
        movt    r3, 16386
        ldr     r2, [r3]
        movw    r3, #4120
        movt    r3, 16386
        orr     r2, r2, #16
        str     r2, [r3]
        movw    r3, #4100
        movt    r3, 16385
        ldr     r2, [r3]
        movw    r3, #4100
        movt    r3, 16385
        bic     r2, r2, #15728640
        str     r2, [r3]
        movw    r3, #4100
        movt    r3, 16385
        ldr     r2, [r3]
        movw    r3, #4100
        movt    r3, 16385
        orr     r2, r2, #1048576
        str     r2, [r3]
        movw    r3, #4108
        movt    r3, 16385
        ldr     r2, [r3]
        movw    r3, #4108
        movt    r3, 16385
        bic     r2, r2, #8192
        str     r2, [r3]
        movs    r3, #0
        str     r3, [r7, #4]
        movs    r3, #0
        str     r3, [r7]
.L6:
        movs    r3, #0
        str     r3, [r7, #4]
        ldr     r3, [r7]
        cmp     r3, #0
        bne     .L2
        ldr     r3, [r7]
        adds    r3, r3, #1
        str     r3, [r7]
        movw    r3, #4108
        movt    r3, 16385
        ldr     r2, [r3]
        movw    r3, #4108
        movt    r3, 16385
        bic     r2, r2, #8192
        str     r2, [r3]
        b       .L4
.L2:
        ldr     r3, [r7]
        subs    r3, r3, #1
        str     r3, [r7]
        movw    r3, #4108
        movt    r3, 16385
        ldr     r2, [r3]
        movw    r3, #4108
        movt    r3, 16385
        orr     r2, r2, #8192
        str     r2, [r3]
        b       .L4
.L5:
        ldr     r3, [r7, #4]
        adds    r3, r3, #1
        str     r3, [r7, #4]
.L4:
        ldr     r2, [r7, #4]
        movw    r3, #16959
        movt    r3, 15
        cmp     r2, r3
        ble     .L5
        b       .L6
SystemInit:
        push    {r7}
        add     r7, sp, #0
        nop
        mov     sp, r7
        ldr     r7, [sp], #4
        bx      lr
