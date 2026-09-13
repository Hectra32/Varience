#include "object.h"
#include "defination.h"
#include "fetch.h"
#include "game.h"
#include "node.h"
#include "text.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

int local_num = 0;

void add_object(GATES type) {

  if (local_num >= MAX_GATES)
    return;

  Gate_Ins *obj = malloc(sizeof(Gate_Ins));

  if (obj == NULL)
    return;

  int sp_x, sp_y;
  spawn_pos(local_num, &sp_x, &sp_y);

  obj->gate = &gate[type];
  obj->local_number = local_num + 1;
  obj->x = sp_x - 50;
  obj->y = sp_y - 25;

  gate_ins[local_num] = obj;

  local_num++;
  add_node(obj);
}

void object_update(Game *game) {

  for (int i = 0; i < local_num; i++) {
    Gate_Ins *obj = gate_ins[i];
    update_node(game, obj);

    if (game->mouse_x > obj->x && game->mouse_x < obj->x + 100 &&
        game->mouse_y > obj->y && game->mouse_y < obj->y + 50 &&
        game->mouse_left_one_f && !game->dragging) {
      game->dragging = 1;
      game->selected = obj;

      game->drag_offset_x = game->mouse_x - obj->x;
      game->drag_offset_y = game->mouse_y - obj->y;
    }
  }

  if (game->dragging && game->selected) {
    game->selected->x = game->mouse_x - game->drag_offset_x;
    game->selected->y = game->mouse_y - game->drag_offset_y;
  }
}

// Thanks For This Function
void object_delete(Game *game) {
  if (game->button[1].type != DELETE_MODE || game->button[1].type_mode != 1 ||
      game->selected == NULL) {
    return;
  }

  Gate_Ins *obj = game->selected;

  /* Remove wires connected to this object's nodes */
  for (int i = 0; i < game->wire_count;) {
    int connected = 0;

    for (size_t n = 0; n < obj->group.node_count; n++) {
      Node *node = &obj->group.node[n];

      if (game->wires[i].from == node || game->wires[i].to == node) {
        connected = 1;
        break;
      }
    }

    if (connected) {
      /* Move the last wire into this slot */
      game->wires[i] = game->wires[game->wire_count - 1];

      game->wire_count--;
      continue;
    }

    i++;
  }

  /* Clear selected_node if it belongs to this object */
  if (game->selected_node != NULL) {
    for (size_t n = 0; n < obj->group.node_count; n++) {
      if (game->selected_node == &obj->group.node[n]) {
        game->selected_node = NULL;
        break;
      }
    }
  }

  /* Free the object's nodes */
  free(obj->group.node);

  /* Find object in gate_ins[] */
  for (int i = 0; i < local_num; i++) {
    if (gate_ins[i] == obj) {

      /* Shift objects after it left */
      for (int j = i; j < local_num - 1; j++) {
        gate_ins[j] = gate_ins[j + 1];
      }

      gate_ins[local_num - 1] = NULL;
      local_num--;

      break;
    }
  }

  /* Clear selection */
  game->selected = NULL;
  game->dragging = 0;
}

void draw_object(Game *game) {

  for (int i = 0; i < local_num; i++) {
    Gate_Ins *obj = gate_ins[i];

    SDL_Rect object = {obj->x, obj->y, obj->gate->width, obj->gate->height};

    SDL_SetRenderDrawColor(game->renderer, obj->gate->color[0],
                           obj->gate->color[1], obj->gate->color[2],
                           obj->gate->color[3]);
    SDL_RenderFillRect(game->renderer, &object);

    switch (obj->gate->id) {
    case AND:
      //      draw_text(game->renderer, game->font, obj->gate->NAME, obj->x,
      //      obj->y,
      //                (SDL_Color){255, 255, 255, 255});

      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;

    case OR:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;

    case NOT:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;

    case NAND:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;

    case NOR:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;

    case XOR:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});

      break;

    case XNOR:
      draw_text_center(game->renderer, game->font, obj->gate->NAME, obj->x,
                       obj->y, obj->gate->width, obj->gate->height,
                       (SDL_Color){255, 255, 255, 255});
      break;
    }
  }
}

// object code
