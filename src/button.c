#include "button.h"

#include "game.h"
#include <stdio.h>

void button_action(Game *game, int id) {

  switch (id) {

  case 1:
    printf("open panel button\n");
    break;

  case 2:
    printf("delete button\n");
    break;
  }
}

void draw_button_icon(Game *game, Button *button) {
  if (button->icon == NULL)
    return;

  int size = button->r + 5;

  SDL_Rect dst = {button->x - size / 2, button->y - size / 2, size, size};

  SDL_RenderCopy(game->renderer, button->icon, NULL, &dst);
}
// new button icon
