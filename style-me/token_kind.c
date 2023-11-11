#include "TOKEN_KIND.h"
#include <ctype.h>

int is_operator_tk(char c)
{
	switch (c)
	{
		default:
			return 0;
		case '*': case '+': case '-': case '/': case '%': case '^': case '!':
			return 1;
	}
};

TokenKind eval_tokenkind(char c)
{
	if (c == '\0')
		return TK_END;
	else if (isspace(c))
		return TK_WHITESPACE;
	else if (isalpha(c))
		return TK_IDENTIFIER;
	else if (isdigit(c))
		return TK_NUMBER;
	else if (is_operator_tk(c))
		return TK_OPERATOR;
	else
		return TK_INVALID;
};

const char* tokenkind_to_str(TokenKind kind)
{
	switch (kind)
	{
		case TK_START:
			return "[START]";
		case TK_END:
			return "[END]";
		case TK_IDENTIFIER:
			return "[IDENTIFIER]";
		case TK_NUMBER:
			return "[NUMBER]";
		case TK_OPERATOR:
			return "[OPERATOR]";
		default:
			return "[INVALID]";
	}
}