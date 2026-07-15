#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "button.h"
#include <panel.h>

#define max_button 2

typedef struct Game{
    SDL_Window* window;
    SDL_Renderer* renderer;

    int running;

    int mouse_x;
    int mouse_y;
    int mouse_left;
    int mouse_right;
    int mouse_left_prev;
    int mouse_left_one_f;

    Button button[max_button];
    Panel panel;

} Game;


#endif

// "why do we use comments"
// - Shunutu
