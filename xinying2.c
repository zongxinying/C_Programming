#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep on Unix-like systems
#ifdef _WIN32
#include <windows.h> // for Windows-specific color handling
#endif

// Define color codes (ANSI escape sequences for Unix-like, Windows-specific for Windows)
#ifdef _WIN32
#define RESET_COLOR ""
#define RED_COLOR   "" // Windows requires a different method to set colors
#define GREEN_COLOR ""
#define BLUE_COLOR  ""
#else
#define RESET_COLOR "\033[0m"
#define RED_COLOR   "\033[31m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR  "\033[34m"
#endif

// Function to clear the screen (ANSI escape sequence for Unix-like, system call for Windows)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

// Function to set text color on Windows (ANSI is not supported by default, so we use system calls)
     #ifdef _WIN32
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wAttributes;
    switch (color) {
        case 0: wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break; // Reset to default (white)
        case 1: wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY; break; // Red
        case 2: wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break; // Green
        case 3: wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break; // Blue
        default: wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
    }
    SetConsoleTextAttribute(hConsole, wAttributes);
}
#endif

// Function to print colored text (uses ANSI on Unix-like, Windows-specific function on Windows)
void printColoredText(const char* text, int color) {
#ifdef _WIN32
    setTextColor(color);
    printf("%s", text);
    setTextColor(0); // Reset to default color after printing
#else
    printf("%s%s%s", (color == 1) ? RED_COLOR : (color == 2) ? GREEN_COLOR : (color == 3) ? BLUE_COLOR : RESET_COLOR, text, RESET_COLOR);
#endif
}

// Simplified animation frame structure
typedef struct {
    char* text;
    int color;
    int x, y; // In this simplified example, we won't actually move the text, but the concept is there
} Frame;

// Function to "draw" a frame (in this case, just print colored text)
void drawFrame(Frame* frame) {
    // In a real implementation, we would need to handle positioning the text on the screen
    // For simplicity, we'll just print it at the start of a new line
    printf("\n");
    printColoredText(frame->text, frame->color);
}

// Main function to demonstrate the concept
                                     int main() {
    Frame frames[] = {
        {"***   ***  *", 1}, // Red text
        {"** **   ****", 2}, // Green text
        {"***** ***  *", 3} // Blue text
    };
    int frameCount = sizeof(frames) / sizeof(frames[0]);

    while (1) { // Infinite loop for animation
        clearScreen();
        for (int i = 0; i < frameCount; i++) {
            drawFrame(&frames[i]);
            // In a real implementation, we would add a delay here
            // usleep(DELAY_US); // Not used in this simplified example
        }
        // In a real implementation, we might want to break out of the loop eventually
        // For now, we'll just keep looping indefinitely
    }
              
    // Note: This example does not actually create an animation in the sense of moving objects
    // or changing states over time. It simply prints colored text in a loop.
    // To create a true animation, you would need to update the state of your objects
    // (e.g., their positions, colors, etc.) in each frame and then redraw them.

    return 0;
}
                                          
