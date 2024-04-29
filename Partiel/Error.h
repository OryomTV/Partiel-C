#pragma once
#include <SDL.h>

int errorSDL(const char* errorMessage);

int errorWindow(const char* errorMessage);

int errorRenderer(const char* errorMessage, SDL_Window* window);