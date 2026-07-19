#ifndef DEFINATION_H
#define DEFINATION_H

#define MAX_GATES 128

// GATE atruct

typedef enum {AND, OR, NOT, NAND, NOR, XOR, XNOR} GATES;

typedef struct {
	char NAME[16];
	GATES id;

	int width;
	int height;

	int color[4];

	int input;
	int output;
} Gate;

typedef struct {
	Gate *gate;
	int number;
	int local_number;

	unsigned int x;
	unsigned int y;
}Gate_Ins;

extern Gate gate[7];
extern Gate_Ins gate_ins[MAX_GATES];
extern int local_num;

void DEFINATION_INIT(void);

#endif

// Comment for no reason
// I dont vibe code
// idk why
// may be bc
// it makes everything worse
// not better
