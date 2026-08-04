#ifndef OBJECT_H
#define OBJECT_H

typedef struct Game Game;
typedef enum GATES GATES;

void add_object(GATES type);
void object_update(Game *game);
void draw_object(Game *game);

#endif
