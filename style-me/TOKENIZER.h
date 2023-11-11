#pragma once
#include "TOKENIZER_OUTPUT.h"
#include <ctype.h>
#include <stdlib.h>

typedef struct Tokenizer
{
	const char* source;
	Token* tokens;
	int cursor;
	int token_count;
	int beg;
	int end;
} Tokenizer;

Tokenizer* create_tokenizer(const char* source);
TokenizerOutput tokenize(Tokenizer* tokenizer);
TokenKind peek_tk(Tokenizer* tokenizer);
char peek_c(Tokenizer* tokenizer);
void advance(Tokenizer* tokenizer);
void add_token(Tokenizer* tokniezer);
void track_add_token(Tokenizer* tokenizer);
void free_tokenizer(Tokenizer* tokenizer);
