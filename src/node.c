#include "node.h"

#include "object.h"
#include "defination.h"
#include "draw.h"


void draw_node(Game* game){
	for(int i = 0; i < local_num; i++){
		Gate_Ins *obj = gate_ins[i];

		int input_node = obj->gate->input;
		int output_node = obj->gate->output;

		int spacing = 19;
		int start = obj->y - ((input_node) * spacing) / 2;


		for(int in = 0; in < input_node; in++){
			SDL_SetRenderDrawColor(game->renderer, 255,255,255,255);
			DrawFilledCircle(game->renderer,
					 obj->x,
					 start + i * spacing,
					 6);
		}
	}
}
