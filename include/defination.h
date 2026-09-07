#ifndef DEFINATION_H
#define DEFINATION_H

#define MAX_GATES 128

// GATE atruct

typedef enum GATES { AND, OR, NOT, NAND, NOR, XOR, XNOR } GATES;

#include "node.h"

typedef struct {
  char NAME[16];
  GATES id;

  int width;
  int height;

  int color[4];

  int input;
  int output;
} Gate;

typedef struct Gate_Ins {
  Gate *gate;
  int number;
  int local_number;

  int x;
  int y;

  Nodes_Group group;
} Gate_Ins;

extern Gate gate[7];
extern Gate_Ins *gate_ins[MAX_GATES];
extern int local_num;

void DEFINATION_INIT(void);

#endif

// Comment for no reason
// I dont vibe code
// idk why
// may be bc
// it makes everything worse
// not better
