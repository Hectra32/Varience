#include "game.h"
#include "defination.h"
#include "object.h"
#include "fetch.h"
#include "text.h"

#include <SDL2/SDL.h>
#include <stdio.h>


int local_num = 0;

void add_object(GATES type){

	Gate_Ins *obj = &gate_ins[local_num];

	int sp_x, sp_y;
	spawn_pos(local_num, &sp_x, &sp_y);

	obj->gate = &gate[type];
	obj->local_number = local_num + 1;
	obj->x = sp_x - 50;
	obj->y = sp_y - 25;

	local_num++;
}

void draw_object(Game* game){

	for(int i = 0; i < local_num; i++){
		Gate_Ins *obj = &gate_ins[i];

		SDL_Rect object =
		{
			obj->x,
			obj->y,
			obj->gate->width,
			obj->gate->height
		};

		SDL_SetRenderDrawColor(game->renderer, obj->gate->color[0], obj->gate->color[1], obj->gate->color[2], obj->gate->color[3]);
		SDL_RenderFillRect(game->renderer, &object);

		if(obj->gate->id == AND){
			draw_text(game->renderer, game->font,
					"AND", obj->x, obj->y,
					(SDL_Color){255,255,255,255});
		}

		else if(obj->gate->id == OR){
			draw_text(game->renderer, game->font,
					"OR", obj->x, obj->y,
					(SDL_Color){255,255,255,255});
		}

		else if(obj->gate->id == NOT){
			draw_text(game->renderer, game->font,
					"NOT", obj->x, obj->y,
					(SDL_Color){255,255,255,255});
		}

	}
}


// object code
