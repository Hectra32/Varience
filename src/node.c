#include "node.h"

#include "defination.h"
#include "draw.h"
#include "object.h"

void divide(int length, int section, int pos[]) {
  for (int i = 0; i < section; i++)
    pos[i] = ((i + 1) * length) / (section + 1);
}

void draw_node(Game *game) {
  for (int i = 0; i < local_num; i++) {
    Gate_Ins *obj = gate_ins[i];

    int input_node = obj->gate->input;
    int output_node = obj->gate->output;

    int gap = 19;
    int in_start = obj->y;
    int ot_start = obj->y;
    int r = 6;

    for (int in = 0; in < input_node; in++) {

      int inp[input_node];
      divide(obj->gate->height, input_node, inp);

      SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
      DrawFilledCircle(game->renderer, obj->x, obj->y + inp[in], r);
    }

    for (int ot = 0; ot < output_node; ot++) {

      int otp[output_node];
      divide(obj->gate->height, output_node, otp);

      SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
      DrawFilledCircle(game->renderer, obj->x + 100, obj->y + otp[ot], r);
    }
  }
}
