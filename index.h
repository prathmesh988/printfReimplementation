#include <stdarg.h> // this library is used to handle the n arguments function

// #include <stdio.h> 👉 for testing the n argument function to replicate the behavior  of printf
// this library is used to handle windows provided api
#include <windows.h>

void print_float(double num, HANDLE hStdout, DWORD *written)
{

    int intPart = (int)num;
    // this buffer is used to store the integer part of the number in char format coz the writeconsole function takes char as input
    char intBuffer[20];
    int intLength = 0;
    while (intPart != 0)
    {
        intBuffer[intLength++] = '0' + (intPart % 10);
        intPart /= 10;
    }
    if (intLength == 0)
    {
        intBuffer[intLength++] = '0';
    }
    for (int i = intLength - 1; i >= 0; i--)
    {
        WriteConsole(hStdout, &intBuffer[i], 1, written, NULL);
    }

    WriteConsole(hStdout, ".", 1, written, NULL);

    double decimalPart = num - (int)num;
    for (int i = 0; i < 6; i++)
    {
        decimalPart *= 10;
        int digit = (int)decimalPart;
        char digitChar = '0' + digit;
        WriteConsole(hStdout, &digitChar, 1, written, NULL);
        decimalPart -= digit;
    }
}
// this method is used to print the float value with the specified precision
void PrecisionFloat(double num, HANDLE hStdout, DWORD *written, int precision)
{
    // Print integer part
    int intPart = (int)num;
    char intBuffer[20];
    int intLength = 0;
    if (intPart == 0)
    {
        intBuffer[intLength++] = '0'; // If integer part is zero, print '0'
    }
    else
    {
        while (intPart != 0)
        {
            intBuffer[intLength++] = '0' + (intPart % 10);
            intPart /= 10;
        }
    }
    for (int i = intLength - 1; i >= 0; i--)
    {
        WriteConsole(hStdout, &intBuffer[i], 1, written, NULL);
    }

    // Print decimal point
    WriteConsole(hStdout, ".", 1, written, NULL);

    // Print decimal part with specified precision
    double decimalPart = num - (int)num;
    for (int i = 0; i < precision; i++)
    {
        decimalPart *= 10;
        int digit = (int)decimalPart;
        char digitChar = '0' + digit;
        WriteConsole(hStdout, &digitChar, 1, written, NULL);
        decimalPart -= digit;
    }

    // Print newline character
}

void my_printf(const char *format, ...)
{
    // this boilor plate is the windows api to handle the console output
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    //taking  the n argumetns and storing it in the va_list which is a pointer to the list of arguments pointer to the list of arguments
    va_list args;
    va_start(args, format);

    // va_arg is used to get the next argument from the list of arguments

    // printf("%p",args);

    // printf("%d",*args);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            if (*format == '\0')
                break;
            if (*format == 'd')
            { // %d

                int num = va_arg(args, int);
                // printf("%d",num);
                char buffer[20]; // Assuming max int is 20 characters long
                int length = 0;
                while (num != 0)
                {
                    buffer[length++] = '0' + (num % 10);
                    num /= 10;
                }
                if (length == 0)
                {
                    buffer[length++] = '0';
                }
                for (int i = length - 1; i >= 0; i--)
                {
                    WriteConsole(hStdout, &buffer[i], 1, &written, NULL);
                }
            }
            else if (*format == 'f')
            { // %f
                double num = va_arg(args, double);
                // printf("%f",num);
                print_float(num, hStdout, &written);
            }
            else if (*format == 's')
            { // %s
                char *str = va_arg(args, char *);
                // printf("%s",str);
                while (*str != '\0')
                {
                    WriteConsole(hStdout, str, 1, &written, NULL);
                    str++;
                }
            }
            else if (*format == 'c')
            { // %c
                char c = (char)va_arg(args, int);
                // printf("%c",c);
                WriteConsole(hStdout, &c, 1, &written, NULL);
            }
            else if (*format == 'l' && *(format + 1) == 'd')
            { // %ld
                format++;

                long num = va_arg(args, long);
                // printf("%ld",num);
                char buffer[20];
                int length = 0;
                while (num != 0)
                {
                    buffer[length++] = '0' + (num % 10);
                    num /= 10;
                }
                if (length == 0)
                {
                    buffer[length++] = '0';
                }
                for (int i = length - 1; i >= 0; i--)
                {
                    WriteConsole(hStdout, &buffer[i], 1, &written, NULL);
                }
            }
            else if (*format == '0' && *(format + 1) == '.' || *format > '0' && *(format + 1) == 'f')
            { // %value.f
                if (*format == '0' && *(format + 1) == '.')
                {
                    format++;
                    format++;
                    int precision = 0;
                    while ((*format) >= '0' && (*format) <= '9')
                    {

                        precision = precision * 10 + (*format - '0');
                        format++;
                    }
                    if (*format == 'f')
                    {
                        double num = va_arg(args, double);
                        PrecisionFloat(num, hStdout, &written, precision);
                    }
                    else
                    {

                        WriteConsole(hStdout, format, 1, &written, NULL);
                    }
                }
                else
                {

                    int precision = 0;
                    while ((*format) >= '0' && (*format) <= '9')
                    {

                        precision = precision * 10 + (*format - '0');
                        format++;
                    }
                    if (*format == 'f')
                    {
                        double num = va_arg(args, double);
                        PrecisionFloat(num, hStdout, &written, precision);
                    }
                    else
                    {
                        WriteConsole(hStdout, format, 1, &written, NULL);
                    }
                }
            }
            else
            {
                format--;
                WriteConsole(hStdout, format, 1, &written, NULL);
            }
        }
        else
        {

            WriteConsole(hStdout, format, 1, &written, NULL);
        }

        format++;
    }

    va_end(args);
}