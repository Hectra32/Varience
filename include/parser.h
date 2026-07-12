#ifndef PARSER_H
#define PARSER_H

typedef struct{
	int id;
	char name[32];
	char shape[16];

	int width;
	int height;

	int color[4];

	int inputs;
	int outputs;
}GateDef;

typedef struct {
	Gate *gate;
	int gate_count;
} GateData;

typedef struct {
	GateDef *def;

	int x;
	int y;

	int input_state[8];
	int output_state[8];
}GateInstance;


#endif
