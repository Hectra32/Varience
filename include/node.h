#ifndef NODE_H
#define NODE_H

#include <stddef.h>

typedef struct Game Game;
typedef struct Gate_Ins Gate_Ins;

typedef enum { Input, Output } Node_type;

typedef struct Node {
  int node_id;
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
void add_node(Gate_Ins *obj);
void update_node(Game *game, Gate_Ins *obj);

extern int rn_gid;
extern int node_id;

#endif
