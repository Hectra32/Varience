#include "defination.h"

#include <string.h>

#define GATES 3

Gate gate[GATES];
Gate_Ins gate_ins[GATES];

void DEFINATION_INIT(void){

	for(int i = 0; i < GATES; i++){
		if(i == AND){
			strcpy(gate[i].NAME, "AND");
			gate[i].id = AND;

			gate[i].width = 200;
			gate[i].height = 100;

			gate[i].color[0] = 255;
			gate[i].color[1] = 255;
			gate[i].color[2] = 255;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}
		
		else if(i == OR){
			strcpy(gate[i].NAME, "OR");
			gate[i].id = OR;

			gate[i].width = 200;
			gate[i].height = 100;

			gate[i].color[0] = 255;
			gate[i].color[1] = 255;
			gate[i].color[2] = 255;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}

		else if(i == NOT){
			strcpy(gate[i].NAME, "NOT");
			gate[i].id = NOT;

			gate[i].width = 200;
			gate[i].height = 100;

			gate[i].color[0] = 255;
			gate[i].color[1] = 255;
			gate[i].color[2] = 255;
			gate[i].color[3] = 255;

			gate[i].input = 1;
			gate[i].output = 1;
		}
		

		gate_ins[i].gate = &gate[i];
		gate_ins[i].number = i+1;
		gate_ins[i].local_number = 0;
		gate_ins[i].x = 0;
		gate_ins[i].y = 0;
	}
}

/* 
 * "code readablity
 * isnt a thing"
 * - the person who wrote this 
 */
