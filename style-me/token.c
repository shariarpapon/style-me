#include "TOKEN.h"
#include <stdlib.h>
#include <string.h>

Token create_token(TokenKind kind, const char* source, int beg, int end)
{
	Token token = { .kind = kind, .source = source, .beg = beg, .end = end };
	return token;
}

const char* get_token_value(Token* token) 
{
	if (token->kind == TK_START)
		return "__source-start__";
	else if (token->kind == TK_END)
		return "__source-end__";
	int len = token->end - token->beg + 1;
	char* value = (char*)malloc(len);
	for (int i = 0; i < len; i++)
		value[i] = token->source[token->beg + i];
	value[len] = '\0';
	return value;
}