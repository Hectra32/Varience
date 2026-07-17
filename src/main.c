#include <SDL2/SDL.h>
#include <stdio.h>

#include "fetch.h"
#include "event.h"
#include "update.h"
#include "draw.h"
#include "game.h"
#include "panel.h"
#include "object.h"
#include "defination.h"


int main(){
	SDL_Init(SDL_INIT_VIDEO);

	int weight, height;
	display_size(&weight,&height);

	Game game;
// Window and Renderer creation
	game.window =
		SDL_CreateWindow(
            		"Varience",
            		100,
            		100,
            		weight,
            		height,
            		0
        	);

	game.renderer =
		SDL_CreateRenderer(
			game.window,
			-1,
			0
		);
// UI deffinition
	game.button[0] = (Button){
		1,// id
		0,// x pos
		15,// y pos
		10,// radius
		0//is pressed
	};
	game.button[0].action = panel_toggle;
	game.button[0].type = PANEL;
	game.button[0].type_mode = 0;// unused for panel toggle option ____

	game.button[1] = (Button){
		2,
		60,
		15,
		10,
		0
	};
	game.button[1].action = NULL;
	game.button[1].type = DELETE_MODE;
	game.button[1].type_mode = 0;


// Panel setup
	panel_init(&game);
// --

//
//
	
	DEFINATION_INIT();

	add_object(AND);


	game.running = 1;
	SDL_Event event;


// Main loop
	while(game.running){
		events(&game);
		update(&game);
		draw(&game);

		game.mouse_left_one_f = 0;

		SDL_Delay(10);
	}

// Clean up
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);

	SDL_Quit();
	return 0;
}


// main code file for
// Varience 
// v_0.00
