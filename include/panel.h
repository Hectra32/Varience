#ifndef PANEL_H
#define PANEL_H

typedef struct {
	int x;
	int y;

	int w;
	int h;

	int target_x;
	int open;

	int speed;
}Panel;

typedef struct Game Game;

void panel_init(Game* game);
void panel_toggle(Game* game);
void panel_update(Game* game);
void panel_draw(Game* game);

#endif
