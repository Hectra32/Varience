#include "node.h"

#include "object.h"
#include "defination.h"
#include "draw.h"


void draw_node(Game* game){
	for(int i = 0; i < local_num; i++){
		Gate_Ins *obj = gate_ins[i];

		int input_node = obj->gate->input;
		int output_node = obj->gate->output;

		int gap = 19;
		int in_start = obj->y;
		int ot_start = obj->y;
		int r = 6;


		for(int in = 0; in < input_node; in++){
			SDL_SetRenderDrawColor(game->renderer, 255,0,255,255);
			DrawFilledCircle(game->renderer,
					 obj->x,
					 in_start +(gap) * in,
					 r);
		}

		for(int ot = 0; ot < output_node; ot++){
			SDL_SetRenderDrawColor(game->renderer, 255,255,0,255);
			DrawFilledCircle(game->renderer,
					obj->x + 100,
					ot_start + (gap) * ot,
					r);
		}
	}
}
