#include <SDL2/SDL.h>

#include "game.h"

void events(Game* game){
	SDL_Event event;
	
	while(SDL_PollEvent(&event)){

		switch(event.type){

			case SDL_QUIT:
				game->running = 0;
				break;

			case SDL_MOUSEMOTION:
				game->mouse_x = event.motion.x;
				game->mouse_y = event.motion.y;
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button){

					case SDL_BUTTON_LEFT:
						game->mouse_left = 1;
						game->mouse_left_one_f = 1;
						break;

					case SDL_BUTTON_RIGHT:
						game->mouse_right = 1;
						break;
				}

				break;

			case SDL_MOUSEBUTTONUP:
				switch(event.button.button){
					case SDL_BUTTON_LEFT:
						game->mouse_left = 0;
						break;

					case SDL_BUTTON_RIGHT:
						game->mouse_right = 0;
						break;
				}

				break;

		}
	
		}	
}
