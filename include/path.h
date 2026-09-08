#ifndef PATH_H
#define PATH_H

#define MAX_WIRES 4096

typedef struct Game Game;
typedef struct Node Node;

typedef struct {
  Node *from;
  Node *to;
} Wire;

int find_path(int x1, int y1, int x2, int y2, int *out_points);

void draw_path(Game *game, int x1, int y1, int x2, int y2);

void draw_paths(Game *game);

#endif
