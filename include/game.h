#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button.h"
#include "defination.h"
#include "node.h"
#include "panel.h"
#include "path.h"

#define max_button 2

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

  int running;

  int mouse_x;
  int mouse_y;
  int mouse_left;
  int mouse_right;
  int mouse_left_prev;
  int mouse_left_one_f;
  int dragging;

  Gate_Ins *selected;
  int drag_offset_x;
  int drag_offset_y;

  Button button[max_button];
  Panel panel;

  Node *selected_node;

  Wire wires[MAX_WIRES];
  int wire_count;
} Game;

#endif

// "why do we use comments"
// - Shunutu
