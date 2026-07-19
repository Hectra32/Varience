#include "game.h"
#include "panel.h"
#include "fetch.h"
#include "object.h"
#include "defination.h"

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



// Panel Update function




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


	if((game->mouse_x >= game->panel.x + 100) &&
	   (game->mouse_x <= game->panel.x + 100 + 100) &&
	   (game->mouse_y >= game->panel.y + 50) &&
	   (game->mouse_y <= game->panel.y + 50 + 50) &&
	   (game->mouse_left_one_f))
	{
		add_object(AND);
	}

	else if((game->mouse_x >= game->panel.x + 300) &&
	  (game->mouse_x <= game->panel.x + 300 + 100) &&
	  (game->mouse_y >= game->panel.y + 50) &&
	  (game->mouse_y <= game->panel.y + 50 + 50) &&
	  (game->mouse_left_one_f))
	{
		add_object(OR);
	}

	else if((game->mouse_x >= game->panel.x + 500) &&
	  (game->mouse_x <= game->panel.x + 500 + 100) &&
	  (game->mouse_y >= game->panel.y + 50) &&
	  (game->mouse_y <= game->panel.y + 50 + 50) &&
	  (game->mouse_left_one_f))
	{
		add_object(NOT);
	}

	else if((game->mouse_x >= game->panel.x + 100) &&
	 (game->mouse_x <= game->panel.x + 100 + 100) &&
	 (game->mouse_y >= game->panel.y + 150) &&
	 (game->mouse_y <= game->panel.y + 150 + 50) &&
	 (game->mouse_left_one_f))
	{
		add_object(NAND);
	}

	else if((game->mouse_x >= game->panel.x + 300) &&
	 (game->mouse_x <= game->panel.x + 300 + 100) &&
	 (game->mouse_y >= game->panel.y + 150) &&
	 (game->mouse_y <= game->panel.y + 150 + 50) &&
	 (game->mouse_left_one_f))
	{
		add_object(NOR);
	}

	else if((game->mouse_x >= game->panel.x + 500) &&
	 (game->mouse_x <= game->panel.x + 500 + 100) &&
	 (game->mouse_y >= game->panel.y + 150) &&
	 (game->mouse_y <= game->panel.y + 150 + 50) &&
	 (game->mouse_left_one_f))
	{
		add_object(XOR);
	}

	else if((game->mouse_x >= game->panel.x + 100) &&
	 (game->mouse_x <= game->panel.x + 100 + 100) &&
	 (game->mouse_y >= game->panel.y + 250) &&
	 (game->mouse_y <= game->panel.y + 250 + 50) &&
	 (game->mouse_left_one_f))
	{
		add_object(XNOR);
	}
}






void draw_panel_object(Game* game){

	for(int i = 0; i < 7; i++){ // change i < 3 if u add more gate
			
		int row = gate[i].id / 3;
		int col = gate[i].id % 3;

		SDL_Rect object = {
			game->panel.x + 100 + col * 200,
			game->panel.y + 50 + row * 100,
			gate[i].width,
			gate[i].height
		};

		SDL_SetRenderDrawColor(	
			game->renderer,
			gate[i].color[0],
			gate[i].color[1],
			gate[i].color[2],
			gate[i].color[3]
		);

		SDL_RenderFillRect(game->renderer, &object);
	}
}






// Panel Draw function


void panel_draw(Game* game){
	
	SDL_Rect panel = {
		game->panel.x,
		game->panel.y,
		game->panel.w,
		game->panel.h
	};

	SDL_SetRenderDrawColor(game->renderer, 60,60,60,255);
	SDL_RenderFillRect(game->renderer, &panel);

	draw_panel_object(game);
}
