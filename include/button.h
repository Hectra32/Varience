#ifndef BUTTON_H
#define BUTTON_H

#include "game.h"

typedef enum {
	PANEL,
	DELETE_MODE,
	SAVE,
	LOAD,
	SETTINGS
}Button_type;

typedef struct Game Game;

typedef struct{
	int id;

	int x;
	int y;

	int r;

	int is_pressed_left;
	int is_pressed_right;

	void (*action) (Game* game);

	Button_type type;
	int type_mode;
} Button;

void button_action(Game* game, int id);

#endif
