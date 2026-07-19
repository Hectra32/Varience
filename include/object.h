#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defination.h"

typedef struct Game Game;


void add_object(GATES type);
void object_update(Game* game);
void draw_object(Game* game);

#endif
