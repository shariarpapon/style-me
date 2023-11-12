#pragma once
#include <ctype.h>
#include <string.h>

#define KEYWORD_begin "begin"
#define KEYWORD_make "make"
#define KEYWORD_call "call"
#define KEYWORD_in "in"
#define KEYWORD_out "out"
#define KEYWORD_pack "pack"
#define KEYWORD_label "label"
#define KEYWORD_container "container"
#define KEYWORD_end "end"
#define KEYWORD_text "text"

///<summary>
///Enum for different types of token. 
///</summary>
typedef enum TokenKind
{
	TK_INVALID,
	TK_END,
	TK_WHITESPACE,
	TK_IDENTIFIER,
	TK_KEYWORD,
	TK_NUMBER,
	TK_OPERATOR,
	TK_ARG_DELIMITER
} TokenKind;

///<returns>
/// 1 if the given character is a argument delimiter.
///</returns>
inline int is_arg_delimiter(char c)
{
	switch (c) 
	{
		case ',':
			return 1;
		default:
			return 0;
	}
}

///<returns>
///1 if the identifier is a keyword or 0 if the identifier did not match a keyword.
///</returns>
inline int is_keyword(const char* value) 
{
	if
	(
		!strcmp(value, KEYWORD_begin) 
		|| !strcmp(value, KEYWORD_make) 
		|| !strcmp(value, KEYWORD_call) 
		|| !strcmp(value, KEYWORD_in) 
		|| !strcmp(value, KEYWORD_out) 
		|| !strcmp(value, KEYWORD_pack) 
		|| !strcmp(value, KEYWORD_label)
		|| !strcmp(value, KEYWORD_container)
		|| !strcmp(value, KEYWORD_end)
		|| !strcmp(value, KEYWORD_text)
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
	else if (is_operator(c))
		return TK_OPERATOR;
	else if (is_arg_delimiter(c))
		return TK_ARG_DELIMITER;
	else
		return TK_INVALID;
};

///<returns>
///A string representation of the given TokenKind.
///</returns>
inline char* tokenkind_to_str(TokenKind kind)
{
	switch (kind)
	{
	case TK_END:
		return "END";
	case TK_IDENTIFIER:
		return "IDENTIFIER";
	case TK_KEYWORD:
		return "KEYWORD";
	case TK_NUMBER:
		return "NUMBER";
	case TK_OPERATOR:
		return "OPERATOR";
	case TK_ARG_DELIMITER:
		return "ARG_DELIMITER";
	default:
		return "INVALID:";
	}
}