#include "game.h"
#include "defination.h"

#include <SDL2/SDL.h>
#include <stdio.h>

void add_object(GATES type){

	int local_num = 0;

	Gate_Ins *obj = &gate_ins[local_num];

	obj->gate = &gate[type];
	obj->local_number = local_num + 1;
	obj->x = 1000;
	obj->y = 1000;

	local_num++;
	printf("add_object called");
}

// object code
