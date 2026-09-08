#include "path.h"
#include "game.h"
#include "node.h"

#include <SDL2/SDL.h>

#define MAX_POINT 1024

int find_path(int x1, int y1, int x2, int y2, int *out_points) {

  int count = 0;

  int x = x1;
  int y = y1;

  while (x != x2 && count < MAX_POINT) {
    out_points[count * 2] = x;
    out_points[count * 2 + 1] = y;
    count++;

    if (x < x2)
      x++;
    else
      x--;
  }

  while (y != y2 && count < MAX_POINT) {
    out_points[count * 2] = x;
    out_points[count * 2 + 1] = y;
    count++;

    if (y < y2)
      y++;
    else
      y--;
  }

  out_points[count * 2] = x2;
  out_points[count * 2 + 1] = y2;
  count++;

  return count;
}

void draw_path(Game *game, int x1, int y1, int x2, int y2) {
  int points[MAX_POINT * 2];

  int count = find_path(x1, y1, x2, y2, points);

  for (int i = 0; i < count; i++) {

    int x = points[i * 2];
    int y = points[i * 2 + 1];

    SDL_RenderDrawPoint(game->renderer, x, y);
  }
}

void draw_paths(Game *game) {
  for (int i = 0; i < game->wire_count; i++) {

    Node *from = game->wires[i].from;
    Node *to = game->wires[i].to;

    draw_path(game, from->x, from->y, to->x, to->y);
  }
}
