#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "button.h"
#include "object.h"


void button_action(Game* game, int id){

	switch(id){

		case 1:
			printf("open panel button\n");
			break;

		case 2:
			printf("delete button\n");
			break;
	}
}
