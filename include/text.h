#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_text( SDL_Renderer *renderer,
		TTF_Font *font,
		const char *text,
		int x,
		int y,
		SDL_Color color);

#endif
