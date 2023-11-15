#pragma once
#include "tokenizer_output.h"
#include <ctype.h>
#include <stdlib.h>

///<summary>
///Holds all relevant information for a tokenizing process.
///</summary>
typedef struct Tokenizer
{
	const char* source;
	Token* tokens;
	TokenKind kind;
	int cursor;
	int token_count;
	int beg;
	int end;
} Tokenizer;

Tokenizer* create_tokenizer(const char* source);
TokenizerOutput tokenize(Tokenizer* tokenizer);
TokenKind peek_tk(Tokenizer* tokenizer, int offset);
TokenKind peek_tk_next_nospace(Tokenizer* tokenizer);
void add_current_token(Tokenizer* tokniezer);
void notrack_add_token(Tokenizer* tokenizer);
char peek_c(Tokenizer* tokenizer, int offset);
void advance(Tokenizer* tokenizer);
void track_add_token(Tokenizer* tokenizer);
void track_add_identifier_token(Tokenizer* tokenizer);
void add_token(Tokenizer* tokenizer, Token token);
void free_tokenizer(Tokenizer* tokenizer);
const char* read_source_file(const char* filepath);
