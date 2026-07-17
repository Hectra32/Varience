#include "game.h"
#include "defination.h"
#include "object.h"
#include "fetch.h"

#include <SDL2/SDL.h>
#include <stdio.h>


int local_num = 0;

void add_object(GATES type){

	printf("Add object type %d\n",type);

	Gate_Ins *obj = &gate_ins[local_num];

	int sp_x, sp_y;
	spawn_pos(local_num, &sp_x, &sp_y);

	obj->gate = &gate[type];
	obj->local_number = local_num + 1;
	obj->x = sp_x;
	obj->y = sp_y;
	printf("drawn object at x: %d, y: %d\n", sp_x, sp_y);

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
	}
}


// object code
