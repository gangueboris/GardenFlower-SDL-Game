#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CELL_SIZE 20

// Structure représentant une position dans le labyrinthe
typedef struct {
    int x;
    int y;
} Position;

void drawMaze(SDL_Surface *screen, int maze[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE]) {
    SDL_Rect rect;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;

    for (int y = 0; y < SCREEN_HEIGHT/CELL_SIZE; y++) {
        for (int x = 0; x < SCREEN_WIDTH/CELL_SIZE; x++) {
            rect.x = x * CELL_SIZE;
            rect.y = y * CELL_SIZE;

            if (maze[y][x] == 1) {
                SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255)); // White cell
            } else {
                SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0)); // Black wall
            }
        }
    }

    SDL_Flip(screen);
}

void drawPoint(SDL_Surface *screen, Position pos) {
    SDL_Rect rect;
    rect.x = pos.x * CELL_SIZE + CELL_SIZE / 4;
    rect.y = pos.y * CELL_SIZE + CELL_SIZE / 4;
    rect.w = CELL_SIZE / 2;
    rect.h = CELL_SIZE / 2;

    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0)); // Red point
    SDL_Flip(screen);
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // Seed for random number generation

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create SDL window
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

    // Generate maze (1 = path, 0 = wall)
    int maze[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];
    for (int y = 0; y < SCREEN_HEIGHT/CELL_SIZE; y++) {
        for (int x = 0; x < SCREEN_WIDTH/CELL_SIZE; x++) {
            if (rand() % 4 == 0) { // Randomly generate walls
                maze[y][x] = 0;
            } else {
                maze[y][x] = 1;
            }
        }
    }

    // Draw maze
    drawMaze(screen, maze);

    // Start position of the point
    Position startPos = {1, 1};
    Position currentPosition = startPos;

    // Main loop for moving the point
    bool quit = false;
    while (!quit) {
        // Clear screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        // Draw maze
        drawMaze(screen, maze);

        // Draw point at current position
        drawPoint(screen, currentPosition);

        // Move point randomly
        int direction = rand() % 4;
        switch (direction) {
            case 0: // Up
                if (currentPosition.y > 0 && maze[currentPosition.y - 1][currentPosition.x] == 1) {
                    currentPosition.y--;
                }
                break;
            case 1: // Down
                if (currentPosition.y < SCREEN_HEIGHT/CELL_SIZE - 1 && maze[currentPosition.y + 1][currentPosition.x] == 1) {
                    currentPosition.y++;
                }
                break;
            case 2: // Left
                if (currentPosition.x > 0 && maze[currentPosition.y][currentPosition.x - 1] == 1) {
                    currentPosition.x--;
                }
                break;
            case 3: // Right
                if (currentPosition.x < SCREEN_WIDTH/CELL_SIZE - 1 && maze[currentPosition.y][currentPosition.x + 1] == 1) {
                    currentPosition.x++;
                }
                break;
        }

        // Quit SDL if user closes window
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Delay to control frame rate
        SDL_Delay(100);

        // Update screen
        SDL_Flip(screen);
    }

    // Quit SDL
    SDL_Quit();

    return 0;
}
