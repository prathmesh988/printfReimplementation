#include <Windows.h>
#include <string.h>
#include <stdio.h>
int main() {
    // Get handles to console input, output, and error
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hStderr = GetStdHandle(STD_ERROR_HANDLE);
    
    // Change console window title
    SetConsoleTitle(TEXT("New Console Title"));

    // Set console window position and size
    SMALL_RECT windowSize = { 0, 0, 79, 49 }; // 80x50 chars, zero-based coordinates
    SetConsoleWindowInfo(hStdout, TRUE, &windowSize);

    // Move cursor to specific position
    COORD cursorPos = { 10, 10 }; // zero-based coordinates
    SetConsoleCursorPosition(hStdout, cursorPos);

    // Other operations like writing to console, changing colors, etc. can be done using WriteConsole() and related functions
    
    // Wait for user input before closing the console window

    //dislay the data into console
    char str[] = "Hello, World!";
    DWORD written;
    WriteConsole(hStdout, str, strlen(str), &written, NULL);
    getchar();
    
    return 0;
}
