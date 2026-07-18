#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "panel.h"

void update(Game* game){

	for(int i = 0;i<max_button;i++){

		Button* b = &game->button[i];

		int dx = game->mouse_x - b->x;
		int dy = game->mouse_y - b->y;


		b->is_pressed_left = 0;
		b->is_pressed_right = 0;

		if(dx*dx + dy*dy <= b->r * b->r){

			if(game->mouse_left_one_f == 1){
				if(i == 0){
					b->action(game);
					panel_update(game);
				}
				if(i == 1){
					if(b->type_mode == 1){
						b->type_mode = 0;
					}
					else if(b->type_mode == 0){
						b->type_mode = 1;
					}
				}
			}

			if(game->mouse_right == 1){
				b->is_pressed_right = 1;
			}
		}
	}

	game->button[0].x = game->panel.x + game->panel.w + 30;

	panel_update(game);
}
