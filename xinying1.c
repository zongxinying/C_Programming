// LED_Animation.c
#include <stdio.h>
#include <unistd.h> // for usleep

#define GRID_WIDTH 10
#define GRID_HEIGHT 10
#define DELAY_US 200000 // 200ms

void clearScreen() {
    // ANSI escape code to clear the screen
    printf("\033[H\033[J");
}

void drawGrid(int grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            printf("%c", grid[x][y] ? '*' : ' ');
        }
        printf("\n");
    }
}

void ledAnimation(int grid[GRID_WIDTH][GRID_HEIGHT]) {
    int x = 0, y = 0, directionX = 1, directionY = 0;
    while (1) { // Infinite loop for animation
        clearScreen();

        // Update LED state
        grid[x][y] = 1;

        // Move to the next position
                                     x += directionX;
        y += directionY;

        // Check for boundary conditions and change direction if necessary
        if (x == GRID_WIDTH - 1) {
            directionX = -1;
            directionY = 0;
        } else if (x == 0) {
            directionX = 1;
            directionY = 1;
        } else if (y == GRID_HEIGHT - 1) {
            directionX = 0;
            directionY = -1;
        } else if (y == 0) {
            directionY = 1;
        }

        // Clear previous LED state
        if (x - directionX >= 0 && x - directionX < GRID_WIDTH && y - directionY >= 0 && y - directionY < GRID_HEIGHT) {
            grid[x - directionX][y - directionY] = 0;
        }

        drawGrid(grid);
        usleep(DELAY_US); // Sleep for a short duration to create animation effect
          }
}

int main() {
    int grid[GRID_WIDTH][GRID_HEIGHT] = {0}; // Initialize all LEDs to off state
    ledAnimation(grid);
    return 0;
}
