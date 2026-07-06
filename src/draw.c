#include "draw.h"
#include "game.h"

#include <SDL2/SDL.h>



void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int r) {
    int x = r, y = 0, p = 1 - r;
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        y++;
        p += (p <= 0) ? (2 * y + 1) : (2 * (y - --x) + 1);
    }
}

void DrawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int r) {
    int x = r, y = 0, p = 1 - r;
    while (x >= y) {
        SDL_RenderDrawLine(renderer, cx - x, cy + y, cx + x, cy + y);
        SDL_RenderDrawLine(renderer, cx - x, cy - y, cx + x, cy - y);
        SDL_RenderDrawLine(renderer, cx - y, cy + x, cx + y, cy + x);
        SDL_RenderDrawLine(renderer, cx - y, cy - x, cx + y, cy - x);
        y++;
        p += (p <= 0) ? (2 * y + 1) : (2 * (y - --x) + 1);
    }
}





void draw(Game* game){

	SDL_SetRenderDrawColor(game->renderer, 24,24,24,255);
	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, 255,255,255,255);

	for(int i = 0; i < max_button; i++){

		Button* b = &game->button[i];


		if(i == 0){
			SDL_SetRenderDrawColor(game->renderer, 100,200,100,255);
			DrawFilledCircle(game->renderer, b->x, b->y, b->r);
		}

		if(i == 1 && game->panel.open == 0){
			if(b->type == DELETE_MODE){
				if(b->type_mode == 0){
					SDL_SetRenderDrawColor(game->renderer, 100,100,100,255);
				}
				else if(b->type_mode == 1){
					SDL_SetRenderDrawColor(game->renderer, 200, 100, 100, 255);
				}
			}
			DrawFilledCircle(game->renderer, b->x, b->y, b->r);
		}
	}

	panel_draw(game);


	SDL_RenderPresent(game->renderer);
}
// draw code for 
// Varience
// v_0.00 dependent
