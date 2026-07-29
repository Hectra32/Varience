#include <SDL2/SDL.h>

#include "fetch.h"

void display_size(int *width, int *height) {
  SDL_DisplayMode mode;

  if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
    *width = mode.w;
    *height = mode.h;
  } else {
    *width = 0;
    *height = 0;
  }
}

void spawn_pos(int number, int *x, int *y) {
  int height, width;
  display_size(&width, &height);

  int base_x = width / 2;
  int base_y = height / 2;

  *x = base_x + (10 * number);
  *y = base_y + (10 * number);
}

Uint64 lastTime = 0;
int frames = 0;
void fps(void) {
  Uint64 now = SDL_GetTicks64();

  frames++;

  if (now - lastTime >= 1000) {
    printf("FPS: %d\n", frames);
    fflush(stdout);

    frames = 0;
    lastTime = now;
  }
}

void divide(int length, int section, int pos[]) {
  for (int i = 0; i < section; i++)
    pos[i] = ((i + 1) * length) / (section + 1);
}
