#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "game.h"


typedef enum {AND, OR, NOT, NAND, NOR, XOR, XNOR} Object_Type;


//==============================================================
typedef enum {
	TOKEN_EOF,

	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,

	TOKEN_LBRACE,
	TOKEN_RBRACE,

	TOKEN_DOT,
	TOKEN_COLON,
	TOKEN_SEMICOLON,
	TOKEN_EQUAL,
	TOKEN_NULL,
	TOKEN_UNKOWN
} TokenType;

typedef enum {
	TYPE_START,
	TYPE_END,

	TYPE_BLOCK_START,
	TYPE_BLOCK_END,

	TYPE_WEGHT,
	TYPE_HEIGHT,

	TYPE_COLOR_R,
	TYPE_COLOR_G,
	TYPE_COLOR_B,
	TYPE_COLOR_A,

	TYPE_INPUT,
	TYPE_OUTPUT
} Type;


//================================================================
typedef struct {
	TokenType type;

	char text[64];

	int number;
} Token;


//==================================================================
typedef struct {
	FILE *file;

	int current;

	int line;

	int coloum;
} Lexer;

//================================================================
typedef struct{
	int r;
	int g;
	int b;
	int a;
}color;

//=================================================================
typedef struct {
	Object_Type type;
	int width;
	int height;
	color color;
	int input;
	int output;
} OBJ;

//===================================================================
void lexer_init(Lexer *lexer, FILE *file);

Token lexer_next_token(Lexer *lexer);

int parse(FILE *file, Game* game);

void get_info(OBJ* obj);

#endif
