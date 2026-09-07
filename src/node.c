#include "node.h"
#include "draw.h"
#include "fetch.h"
#include "object.h"

int rn_gid = 1;

void add_node(Gate_Ins *obj) {
  Nodes_Group group;

  group.node_count = obj->gate->input + obj->gate->output;
  group.node = malloc(sizeof(*group.node) * group.node_count);

  for (int i = 0; i < group.node_count; i++) {
    group.node[i].igid = rn_gid++;
    group.node[i].signal = 0;
    group.node[i].x = 0;
    group.node[i].y = 0;
    group.node[i].is_selected = 0;

    if (i < obj->gate->input)
      group.node[i].type = Input;
    else
      group.node[i].type = Output;
  }
}

void draw_node(Game *game) {
  for (int i = 0; i < local_num; i++) {
    Gate_Ins *obj = gate_ins[i];

    if (obj == NULL || obj->gate == NULL)
      continue;

    int input_node = obj->gate->input;
    int output_node = obj->gate->output;
    int r = 6;

    int inp[input_node];
    int otp[output_node];

    if (input_node > 0)
      divide_gap(obj->gate->height, input_node, inp);

    if (output_node > 0)
      divide_gap(obj->gate->height, output_node, otp);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

    for (int in = 0; in < input_node; in++) {
      DrawFilledCircle(game->renderer, obj->x, obj->y + inp[in], r);
    }

    for (int ot = 0; ot < output_node; ot++) {
      DrawFilledCircle(game->renderer, obj->x + 100, obj->y + otp[ot], r);
    }
  }
}
