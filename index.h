#include <stdarg.h>
#include <stdio.h>
//this library is used to handle windows provided api 
#include <windows.h>

void print_float(double num, HANDLE hStdout, DWORD *written) {
  
    int intPart = (int)num;
    char intBuffer[20];
    int intLength = 0;
    while (intPart != 0) {
        intBuffer[intLength++] = '0' + (intPart % 10);
        intPart /= 10;
    }
    if (intLength == 0) {
        intBuffer[intLength++] = '0';
    }
    for (int i = intLength - 1; i >= 0; i--) {
        WriteConsole(hStdout, &intBuffer[i], 1, written, NULL);
    }

 
    WriteConsole(hStdout, ".", 1, written, NULL);

 
    double decimalPart = num - (int)num;
    for (int i = 0; i < 6; i++) { 
        decimalPart *= 10;
        int digit = (int)decimalPart;
        char digitChar = '0' + digit;
        WriteConsole(hStdout, &digitChar, 1, written, NULL);
        decimalPart -= digit;
    }
}


void my_printf(const char *format, ...) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    va_list args;
    va_start(args, format);

    // printf("%p",args);

    // printf("%d",*args);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == '\0')
                break;
            if (*format == 'd') { // %d
                
                int num = va_arg(args, int);
                // printf("%d",num);
                char buffer[20]; // Assuming max int is 20 characters long
                int length = 0;
                while (num != 0) {
                    buffer[length++] = '0' + (num % 10);
                    num /= 10;
                }
                if (length == 0) {
                    buffer[length++] = '0';
                }
                for (int i = length - 1; i >= 0; i--) {
                    WriteConsole(hStdout, &buffer[i], 1, &written, NULL);
                }
            } 
            
            
            else if (*format == 'f') { // %f
                double num = va_arg(args, double);
                // printf("%f",num);
                print_float(num, hStdout, &written);
            } else if (*format == 's') { // %s
                char *str = va_arg(args, char*);
                // printf("%s",str);
                while (*str != '\0') {
                    WriteConsole(hStdout, str, 1, &written, NULL);
                    str++;
                }
            } else if (*format == 'c') { // %c
                char c = (char)va_arg(args, int);
                // printf("%c",c);
                WriteConsole(hStdout, &c, 1, &written, NULL);
            } 
            // else if (*format == 'l' && *(format + 1) == 'd') { // %ld
            //     long num = va_arg(args, long);
            //     char buffer[20]; 
            //     int length = 0;
            //     while (num != 0) {
            //         buffer[length++] = '0' + (num % 10);
            //         num /= 10;
            //     }
            //     if (length == 0) {
            //         buffer[length++] = '0';
            //     }
            //     for (int i = length - 1; i >= 0; i--) {
            //         WriteConsole(hStdout, &buffer[i], 1, &written, NULL);
            //     }
            // }
            
             else { 
                WriteConsole(hStdout, format - 1, 2, &written, NULL);
            }
        } else {
            WriteConsole(hStdout, format, 1, &written, NULL);
        }
        format++;
    }

    va_end(args);
    //to free arge pointer
}