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



void spawn_pos(int number, int* x, int* y)
{
	int height, width;
	display_size(&width, &height);

	int base_x = width/2;
	int base_y = height/2;

	*x = base_x + (20 * number);
	*y = base_y + (20 * number);	
}
