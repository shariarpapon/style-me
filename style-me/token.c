#include "TOKEN.h"
#include <stdlib.h>
#include <string.h>

///<returns>
///A token with the given data.
///</returns>
Token create_token(TokenKind kind, const char* source, int beg, int end)
{
	Token token = { .kind = kind, .source = source, .beg = beg, .end = end};
	return token;
}

///<returns>
///The string value of the current token.
///</returns>
const char* get_token_value(Token token)
{
	if (token.kind == TK_END)
		return "";
	int len = token.end - token.beg + 1;
	char* value = (char*)calloc(len, sizeof(char));
	for (int i = 0; i < len; i++)
		value[i] = token.source[token.beg + i];
	value[len] = '\0';
	return (const char*)value;
}

///<returns>
///The string value of the current token with the given data.
///</returns>
const char* get_token_value_raw(const char* source, int beg, int end)
{
	int len = end - beg + 1;
	char* value = (const char*)calloc(len, sizeof(char));
	for (int i = 0; i < len; i++)
		value[i] = source[beg + i];
	value[len] = '\0';
	return (const char*)value;
}