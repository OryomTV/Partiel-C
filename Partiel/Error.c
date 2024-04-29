#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int errorSDL(const char* errorMessage) {
    fprintf(stderr, "Error: %s\n", errorMessage);
    return -1;
}

int errorWindow(const char* errorMessage) {
    fprintf(stderr, "Error: %s\n", errorMessage);
    SDL_Quit();
    return -1;
}

int errorRenderer(const char* errorMessage, SDL_Window* window) {
    fprintf(stderr, "Error: %s\n", errorMessage);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
}