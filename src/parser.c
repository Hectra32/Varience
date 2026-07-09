/*
 * This file is divided into two parts
 * Lexer
 * and
 * Parser
*/

#include <stdio.h>

#include "game.h"
#include "parser.h"


//================================= LEXER ===============================================

void lexer_init(Lexer *lexer, FILE *file){
	lexer->file = file;

	lexer->current = fgetc(file);

	lexer->line = 0;
	lexer->coloum = 0;
}

static void lexer_next(Lexer *lexer)
{
	if (lexer->current == '\n')
	{
		lexer->line++;
		lexer->coloum = 1;
	}
	else
	{
		lexer->coloum++;
	}

	lexer->current = fgetc(lexer->file);
}

static void skip_whitespace(Lexer *lexer)
{
while (lexer->current == ' ' ||
	lexer->current == '\t' ||
	lexer->current == '\n' ||
	lexer->current == '\r')
	{
		lexer_next(lexer);
	}
}

Token lexer_next_token(Lexer *lexer){
	Token token = {0};

	skip_whitespace(lexer);

	if (lexer->current == EOF)
	{
		token.type = TOKEN_EOF;
		return token;
	}

	if (isalpha(lexer->current))
	{
		int i = 0;
	
		while (isalnum(lexer->current) || lexer->current == '_')
		{
			token.text[i++] = lexer->current;
			lexer_next(lexer);
		}
		token.text[i] = '\0';
		token.type = TOKEN_IDENTIFIER;
		return token;
	}

	if (isdigit(lexer->current))
	{
		token.number = 0;

		while (isdigit(lexer->current))
		{
			token.number *= 10;
			token.number += lexer->current - '0';
			lexer_next(lexer);
		}
		token.type = TOKEN_NUMBER;
		return token;
	}

	switch (lexer->current)
	{

	case '.':
		lexer_next(lexer);
		token.type = TOKEN_DOT;
		return token;

	case '{':
		lexer_next(lexer);
		token.type = TOKEN_LBRACE;
		return token;

	case '}':
		lexer_next(lexer);
		token.type = TOKEN_RBRACE;
		return token;

	case ':':
		lexer_next(lexer);
		token.type = TOKEN_COLON;
		return token;

	case ';':
		lexer_next(lexer);
		token.type = TOKEN_SEMICOLON;
		return token;

	case '=':
		lexer_next(lexer);
		token.type = TOKEN_EQUAL;
		return token;
	}

	printf("Unknown Characcter '%c'\n",lexer->current);
	lexer_next(lexer);

	token.type = TOKEN_EOF;

	return token;


}

//================================= PARSER ==============================================



int parse(FILE *file, Game* game){

	Lexer lexer;

	lexer_init(&lexer, file);

	while(1){
		Token token = lexer_next_token(&lexer);

		if(token.type == TOKEN_EOF)
			break;

		switch(token.type)
		{
			case 0:
				printf("EOF");
				break;

			case 1:
				printf("%s\n",token.text);
				break;

			case 2:
				printf("%d\n",token.number);
				break;

			case 3:
				printf("left brace\n");
				break;

			case 4:
				printf("right brace\n");
				break;

			case 5:
				printf("dot\n");
				break;

			case 6:
				printf("colon\n");
				break;

			case 7:
				printf("semicolon\n");
				break;

			case 8:
				printf("equal\n");
				break;
		}
	}

	return 0;
}

void get_info(OBJ* obj){

}
