#include <SDL2/SDL.h>
#include <stdio.h>
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

	printf("number = %d\n", number);

	int base_x = width/2;
	int base_y = height/2;

	for(int i = 0; i < number + 1; i++){
		*x = base_x + (20 * i);
		*y = base_y + (20 * i);
	}
}
