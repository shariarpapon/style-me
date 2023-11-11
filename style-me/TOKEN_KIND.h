#pragma once

///<summary>
///Enum for different types of token. 
///</summary>
typedef enum TokenKind
{
	TK_START,
	TK_INVALID,
	TK_END,
	TK_WHITESPACE,
	TK_IDENTIFIER,
	TK_NUMBER,
	TK_OPERATOR,
} TokenKind;

int is_operator_tk(char c);
TokenKind eval_tokenkind(char c);
const char* tokenkind_to_str(TokenKind kind);