#ifndef DEFINATION_H
#define DEFINATION_H


// GATE atruct

typedef enum {AND, OR, NOT} GATES;

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

	int x;
	int y;
}Gate_Ins;

extern Gate gate[3];
extern Gate_Ins gate_ins[3];
extern int local_num;

void DEFINATION_INIT(void);

#endif

// Comment for no reason
// I dont vibe code
// idk why
// may be bc
// it makes everything worse
// not better
