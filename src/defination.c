#include "defination.h"

#include <string.h>
#include <stdio.h>


#define GATES 7

Gate gate[GATES]; // Change this if u add more gates :)
Gate_Ins gate_ins[MAX_GATES];

void DEFINATION_INIT(void){

	for(int i = 0; i < GATES; i++){
		if(i == AND){
			strcpy(gate[i].NAME, "AND");
			gate[i].id = AND;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 80;
			gate[i].color[1] = 190;
			gate[i].color[2] = 110;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}
		
		else if(i == OR){
			strcpy(gate[i].NAME, "OR");
			gate[i].id = OR;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 190;
			gate[i].color[1] = 120;
			gate[i].color[2] = 80;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}

		else if(i == NOT){
			strcpy(gate[i].NAME, "NOT");
			gate[i].id = NOT;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 120;
			gate[i].color[1] = 120;
			gate[i].color[2] = 190;
			gate[i].color[3] = 255;

			gate[i].input = 1;
			gate[i].output = 1;
		}

		else if(i == NAND){
			strcpy(gate[i].NAME, "NAND");
			gate[i].id = NAND;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 190;
			gate[i].color[1] = 80;
			gate[i].color[2] = 80;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}

		else if(i == NOR){
			strcpy(gate[i].NAME, "NOR");
			gate[i].id = NOR;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 200;
			gate[i].color[1] = 200;
			gate[i].color[2] = 90;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}

		else if(i == XOR){
			strcpy(gate[i].NAME, "XOR");
			gate[i].id = XOR;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 150;
			gate[i].color[1] = 90;
			gate[i].color[2] = 200;
			gate[i].color[3] = 255;

			gate[i].input = 2;
			gate[i].output = 1;
		}

		else if(i == XNOR){
			strcpy(gate[i].NAME, "XNOR");
			gate[i].id = XNOR;

			gate[i].width = 100;
			gate[i].height = 50;

			gate[i].color[0] = 90;
			gate[i].color[1] = 200;
			gate[i].color[2] = 200;
			gate[i].color[3] = 255;

			gate[i].input = 2;
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
