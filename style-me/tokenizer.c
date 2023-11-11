#include "TOKENIZER.h"
#include <string.h>
#include <stdio.h>

Tokenizer* create_tokenizer(const char* source) 
{
	Tokenizer* tokenizer = calloc(1, sizeof(Tokenizer));
	tokenizer->tokens = calloc(strlen(source) + 1, sizeof(Token));
	tokenizer->source = source;
	tokenizer->token_count = 0;
	tokenizer->cursor = 0;
	tokenizer->beg = 0;
	tokenizer->end = 0;
	
	if (tokenizer == NULL || tokenizer->tokens == NULL) 
	{
		perror("Memory allocation failed. Unable to initialize tokenizer.");
		return NULL;
	}
	
	return tokenizer;
}

TokenizerOutput* tokenize(Tokenizer* tokenizer)
{
	add_token(tokenizer, TK_START);
	int is_source_end = 0;
	while (!is_source_end)
	{
		switch (peek_tk(tokenizer, 0)) 
		{
			case TK_END:
				add_token(tokenizer, TK_END);
				is_source_end = 1;
				break;
			case TK_INVALID: 
				track_add_tokenkind(tokenizer, TK_INVALID);
				break;
			case TK_WHITESPACE: 
				advance(tokenizer);
				break; 
			case TK_IDENTIFIER: 
				track_add_tokenkind(tokenizer, TK_IDENTIFIER);
				break; 
			case TK_NUMBER:
				track_add_tokenkind(tokenizer, TK_NUMBER);
				break; 
		}
	}
	return create_tokenizer_output(tokenizer->tokens, tokenizer->token_count);
}

void advance(Tokenizer* tokenizer)
{
	tokenizer->cursor++;
}

void add_token(Tokenizer* tokenizer, TokenKind kind)
{
	tokenizer->tokens[tokenizer->token_count] = create_token(kind, tokenizer->source, tokenizer->beg, tokenizer->end);
	tokenizer->token_count++;
}

void track_add_tokenkind(Tokenizer* tokenizer, TokenKind kind)
{

	tokenizer->beg = tokenizer->cursor;
	while (peek_tk(tokenizer, 0) == kind)
		advance(tokenizer);
	tokenizer->end = tokenizer->cursor - 1;
	add_token(tokenizer, kind);
}

char peek_c(Tokenizer* tokenizer, int offset)
{
	if (tokenizer->cursor + offset >= strlen(tokenizer->source))
		return '\0';

	return tokenizer->source[tokenizer->cursor + offset];
}

TokenKind peek_tk(Tokenizer* tokenizer, int offset)
{
	return eval_tokenkind(peek_c(tokenizer, offset));
}



