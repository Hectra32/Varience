#include "game.h"
#include "panel.h"
#include "fetch.h"

#include <stdio.h>

void panel_init (Game* game) {

	int weight,height;
	display_size(&weight, &height);


	game->panel.x = -700;
	game->panel.y = 0;

	game->panel.w = 700;
	game->panel.h = height;

	game->panel.target_x = 0;
	game->panel.open = 0;

	game->panel.speed = 10;
}

void panel_toggle(Game* game){
	if(game->panel.open == 0){
		game->panel.open = 1;}
	else if (game->panel.open == 1){
		game->panel.open = 0;}
}

void panel_update(Game* game){
	if(game->panel.open){
		if(game->panel.x < game->panel.target_x){
			while(game->panel.x < game->panel.target_x){
				game->panel.x += game->panel.speed;
			}
		}
	}

	if(! game->panel.open){
		if(game->panel.x <= game->panel.target_x){
			while(game->panel.x > -700){
				game->panel.x -= game->panel.speed;
			}
		}
	}
}

void panel_draw(Game* game){
	
	SDL_Rect panel = {
		game->panel.x,
		game->panel.y,
		game->panel.w,
		game->panel.h
	};

	SDL_SetRenderDrawColor(game->renderer, 50,50,50,255);
	SDL_RenderFillRect(game->renderer, &panel);
}
