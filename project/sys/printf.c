#include <stdarg.h>

#include "sys.h"
// #pragma import(__use_no_semihosting)
// struct __FILE {
//     int handle;
// };

// FILE __stdout;
// void _sys_exit(int x) {
//     x = x;
// }


// // 实现fputc接口
// int fputc(int ch, FILE* f) {
//     // USART_SendString(USART1, (uint8_t)ch);
//     // SendByte(ch);
//     USART_SendData(USART1, (uint8_t)ch);
//     while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {};
//     return ch;
// }

// int fgetc(FILE* f) {
//     while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {}
//     return (uint8_t)USART_ReceiveData(USART1);
// }



int _write(int fd, char* ptr, int len) {
    int i = 0;

    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
    * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2) {
        return -1;
    }

    while (*ptr && (i < len)) {
        USART_SendData(USART1, *ptr);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {};
        if (*ptr == '\n') {
            USART_SendData(USART1, '\r');
            while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {};
        }
        i++;
        ptr++;
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

    // while (*ptr != '\0') {
    //     i++;
    //     USART_SendData(USART1, *ptr++);
    // }
    // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

    return i;
}



void printx(char* str, ...) {
    // va_list valist;
    // int num = 2;
    // int i;
    // va_start(valist, num);
    // // printf(str, va_arg(valist,0),va_arg(valist,1));
    // for (i = 0; i < num; i++)
    // {
    //    sum += va_arg(valist, int);
    // }
    // fflush(stdout);
    // va_end(valist);
}
