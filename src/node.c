#include "node.h"
#include "draw.h"
#include "fetch.h"
#include "object.h"

int rn_gid = 1;

void add_node(Gate_Ins *obj) {
  obj->group.node_count = obj->gate->input + obj->gate->output;

  obj->group.node = malloc(sizeof(*obj->group.node) * obj->group.node_count);

  if (obj->group.node == NULL) {
    obj->group.node_count = 0;
    return;
  }

  for (size_t i = 0; i < obj->group.node_count; i++) {
    obj->group.node[i].igid = rn_gid++;
    obj->group.node[i].signal = 0;
    obj->group.node[i].x = 0;
    obj->group.node[i].y = 0;
    obj->group.node[i].is_selected = 0;

    obj->group.node[i].type = (i < obj->gate->input) ? Input : Output;
  }
}

void update_node(Game *game, Gate_Ins *obj) {
  for (int i = 0; i < obj->group.node_count; i++) {
    if ((game->mouse_x - obj->group.node[i].x) *
                    (game->mouse_x - obj->group.node[i].x) +
                (game->mouse_y - obj->group.node[i].y) *
                    (game->mouse_y - obj->group.node[i].y) <=
            (6 * 6) &&
        (game->mouse_left_one_f ==
         1)) // The Rdius of node in Draw Node function  as 6
    {
      obj->group.node[i].is_selected = 1;
      printf("A noed is selected \n");
    }
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
      Node *node = &obj->group.node[in];

      node->x = obj->x;
      node->y = obj->y + inp[in];

      DrawFilledCircle(game->renderer, node->x, node->y, r);
    }

    for (int ot = 0; ot < output_node; ot++) {
      Node *node = &obj->group.node[input_node + ot];

      node->x = obj->x + obj->gate->width;
      node->y = obj->y + otp[ot];

      DrawFilledCircle(game->renderer, node->x, node->y, r);
    }
  }
}
