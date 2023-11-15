#pragma once
#include "token_kind.h"

inline const char* tk_to_string(TokenKind kind) 
{
	switch (kind)
	{
		default: return "UNKNOWN";
		case TK_INVALID: return "TK_INVALID";
		case TK_END: return "TK_END";
		case TK_WHITESPACE: return "TK_WHITESPACE";
		case TK_IDENTIFIER: return "TK_IDENTIFIER";
		case TK_ACCESS_MOD: return "TK_ACCESS_MOD";
		case TK_SCOPE_MOD: return "TK_SCOPE_MOD";
		case TK_NUMBER: return "TK_NUMBER";
	}
}