#include "button.h"

#include "game.h"
#include <stdio.h>

void button_action(Game *game, int id) {

  switch (id) {

  case 1:
    printf("open panel button\n");
    break;

  case 2:
    printf("delete button\n");
    break;
  }
}
