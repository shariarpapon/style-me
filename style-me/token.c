#include "token.h"
#include "string_utils.h"
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
	return get_token_value_raw(token.source, token.beg, token.end);
}

///<returns>
///The string value of the current token with the given data.
///</returns>
const char* get_token_value_raw(const char* source, int beg, int end)
{
	if (beg == -1 || end == -1)
		return "";
	return get_substr_fromto(source, beg, end);
}