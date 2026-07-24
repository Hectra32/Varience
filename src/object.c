#include "game.h"
#include "defination.h"
#include "object.h"
#include "fetch.h"
#include "text.h"
#include "node.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


int local_num = 0;

void add_object(GATES type){

	if(local_num >= MAX_GATES)
		return;

	Gate_Ins *obj = malloc(sizeof(Gate_Ins));

	if(obj == NULL)
		return;

	int sp_x, sp_y;
	spawn_pos(local_num, &sp_x, &sp_y);

	obj->gate = &gate[type];
	obj->local_number = local_num + 1;
	obj->x = sp_x - 50;
	obj->y = sp_y - 25;

	gate_ins[local_num] = obj;

	local_num++;
}

void object_update(Game* game){
	

	for(int i = 0; i < local_num; i++){
		Gate_Ins *obj = gate_ins[i];

		if(game->mouse_x > obj->x &&
		   game->mouse_x < obj->x + 100 &&
		   game->mouse_y > obj->y &&
		   game->mouse_y < obj->y + 50 &&
		   game->mouse_left_one_f &&
		   ! game->dragging)
		{
			game->dragging = 1;
			game->selected = obj;

			game->drag_offset_x = game->mouse_x - obj->x;
			game->drag_offset_y = game->mouse_y - obj->y;
		}
	}

	if(game->dragging && game->selected){
		game->selected->x = game->mouse_x - game->drag_offset_x;
		game->selected->y = game->mouse_y - game->drag_offset_y;
	}
}

void object_delete(Game* game){
	for(int i = 0; i < local_num; i++){
	
		Gate_Ins *obj = gate_ins[i];
		Button *b = &game->button[i];

		if(b->type == DELETE_MODE && b->type_mode == 1 && game->selected == obj){
			free(obj);
		}
	}
}

void draw_object(Game* game){

	for(int i = 0; i < local_num; i++){
		Gate_Ins *obj = gate_ins[i];

		SDL_Rect object =
		{
			obj->x,
			obj->y,
			obj->gate->width,
			obj->gate->height
		};

		SDL_SetRenderDrawColor(game->renderer, obj->gate->color[0], obj->gate->color[1], obj->gate->color[2], obj->gate->color[3]);
		SDL_RenderFillRect(game->renderer, &object);

		switch(obj->gate->id){
			case AND:
				draw_text(game->renderer, game->font,
					obj->gate->NAME, obj->x, obj->y,
					(SDL_Color){255,255,255,255});
				break;
		

			case OR:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;

			case NOT:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;

			case NAND:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;

			case NOR:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;

			case XOR:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;

			case XNOR:
				draw_text(game->renderer, game->font,
						obj->gate->NAME, obj->x, obj->y,
						(SDL_Color){255,255,255,255});
				break;


		}

		draw_node(game);
	}
}


// object code
