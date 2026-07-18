#include "text.h"
#include "game.h"

void draw_text( SDL_Renderer *renderer,
		TTF_Font *font,
		const char *text,
		int x,
		int y,
		SDL_Color color)
{
	SDL_Surface *surface = 
		TTF_RenderText_Blended(font, text, color);

	SDL_Texture *texture =
		SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect = {x, y, surface->w, surface->h};

	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
}
