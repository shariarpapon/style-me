#pragma once
#include "TOKEN_KIND.h"

typedef struct Token Token;

///<summary>
///Holds all relevant data for a token.
///</summary>
typedef struct Token
{
	TokenKind kind;
	const char* source;
	int beg;
	int end;
} Token;

Token create_token(TokenKind kind, const char* source, int beg, int end);
const char* get_token_value(Token token);
const char* get_token_value_raw(const char* source, int beg, int end);