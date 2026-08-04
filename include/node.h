#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Game Game;

typedef enum { Input, Output } Node_type;

typedef struct {
  int igid;
  int signal;
  int x;
  int y;
  int is_selected;
  Node_type type;
} Node;

typedef struct Nodes_Group {
  int attached_gate_id;

  Node *node;
  size_t node_count;

  int input_nodes;
  int output_nodes;

} Nodes_Group;

void draw_node(Game *game);

extern int rn_gid;

#endif
