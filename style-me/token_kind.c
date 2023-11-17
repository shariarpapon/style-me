#include "token_kind.h"

/// <summary>
/// Returns 1 if the given string is a access modifier (eg. public, private, etc.). Otherwise returns 0.
/// </summary>
int is_access_mod(const char* value)
{
	if
		(
			!strcmp(value, KEYWORD_public)
			|| !strcmp(value, KEYWORD_private)
			|| !strcmp(value, KEYWORD_protected)
			|| !strcmp(value, KEYWORD_internal)
			) return 1;

	return 0;
}

/// <summary>
/// Returns 1 if the given string is a scope modifier (eg. static, const). Otherwise returns 0.
/// </summary>
int is_scope_mod(const char* value)
{
	if
		(
			!strcmp(value, KEYWORD_static)
			|| !strcmp(value, KEYWORD_const)
			) return 1;

	return 0;
}


///<returns>
/// 1 if the given character is an operator, otherwise returns 0.
///</returns>
int is_operator(char c)
{
	switch (c)
	{
	default:
		return 0;
	case '*': case '+': case '-': case '/': case '%':
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
	else
		return TK_INVALID;
};