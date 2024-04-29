#include <SDL.h>
#include <stdbool.h>
#include "Error.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 20

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
    int x, y;
} Square;

Square snake[100];
int snakeLength = 1;
int directionX = 1, directionY = 0;
Square food;

void initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init < 0) {
        errorSDL("SDL marche pas");
    }
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        errorWindow("La window marche pas");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        errorRenderer("Le renderer marche pas", window);
    }

    snake[0].x = SCREEN_WIDTH / 2;
    snake[0].y = SCREEN_HEIGHT / 2;
    food.x = rand() % (SCREEN_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
    food.y = rand() % (SCREEN_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
}

void handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            exit(0);
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                if (directionY != 1) {
                    directionX = 0;
                    directionY = -1;
                }
                break;
            case SDLK_DOWN:
                if (directionY != -1) {
                    directionX = 0;
                    directionY = 1;
                }
                break;
            case SDLK_LEFT:
                if (directionX != 1) {
                    directionX = -1;
                    directionY = 0;
                }
                break;
            case SDLK_RIGHT:
                if (directionX != -1) {
                    directionX = 1;
                    directionY = 0;
                }
                break;
            }
        }
    }
}

bool checkCollision(int x, int y) {
    for (int i = 0; i < snakeLength; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return true;
        }
    }
    return false;
}

void update() {
    int newX = snake[0].x + directionX * SQUARE_SIZE;
    int newY = snake[0].y + directionY * SQUARE_SIZE;

    if (newX >= SCREEN_WIDTH || newX < 0 || newY >= SCREEN_HEIGHT || newY < 0 || checkCollision(newX, newY)) {
        exit(0);
    }

    snakeLength++;
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    snake[0].x = newX;
    snake[0].y = newY;

    if (snake[0].x == food.x && snake[0].y == food.y) {
        food.x = rand() % (SCREEN_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
        food.y = rand() % (SCREEN_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
    }
    else {
        snakeLength--;
    }
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 107, 142, 35, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,50, 205, 50, 255);
    for (int i = 0; i < snakeLength; i++) {
        SDL_Rect rect = { snake[i].x, snake[i].y, SQUARE_SIZE, SQUARE_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 178, 34, 34, 255);
    SDL_Rect rect = { food.x, food.y, SQUARE_SIZE, SQUARE_SIZE };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

int main() {
    initialize();
    while (1) {
        handleInput();
        update();
        draw();
        SDL_Delay(100);
    }
    return 0;
}