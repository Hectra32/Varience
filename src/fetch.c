#include <SDL2/SDL.h>
#include "fetch.h"

void display_size(int* width, int* height)
{
    SDL_DisplayMode mode;

    if (SDL_GetCurrentDisplayMode(0, &mode) == 0)
    {
        *width = mode.w;
        *height = mode.h;
    }
    else
    {
        *width = 0;
        *height = 0;
    }
}
