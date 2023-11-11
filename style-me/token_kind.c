#include "TOKEN_KIND.h"
#include <ctype.h>

///<returns>
/// 1 (true) if the given character is an operator, otherwise returns 0 (false).
///</returns>
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

///<returns>
///The evaluated TokenKind of the given character.
///</returns>
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

///<returns>
///A string representation of the given TokenKind.
///</returns>
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