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

int is_access_mod(const char* value);
int is_scope_mod(const char* value);
int is_operator(char c);
TokenKind eval_tokenkind(char c);