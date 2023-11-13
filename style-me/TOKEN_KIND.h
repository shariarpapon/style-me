#pragma once
#include <ctype.h>
#include <string.h>

//C# access mods
#define KEYWORD_public "public"
#define KEYWORD_private "private"
#define KEYWORD_protected "protected"
#define KEYWORD_internal "internal"

//C# scope mods
#define KEYWORD_static "static"
#define KEYWORD_const "const"

//C# property keywords
#define KEYWORD_get "get"
#define KEYWORD_set "set"

///<summary>
///Enum for different types of token. 
///</summary>
typedef enum TokenKind
{
	TK_INVALID,
	TK_END,
	TK_WHITESPACE,
	TK_IDENTIFIER,
	TK_ACCESS_MOD,
	TK_SCOPE_MOD,
	TK_NUMBER
} TokenKind;

/// <summary>
/// Returns 1 if the given string is a access modifier (eg. public, private, etc.). Otherwise returns 0.
/// </summary>
inline int is_access_mod(const char* value) 
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
inline int is_scope_mod(const char* value) 
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
inline int is_operator(char c)
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
inline TokenKind eval_tokenkind(char c)
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