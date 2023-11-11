#include "TOKENIZER.h"
#include <string.h>
#include <stdio.h>


///<returns>
///A tokenizer pointer initialized with the source string.
///</returns>
Tokenizer* create_tokenizer(const char* source) 
{
	Tokenizer* tokenizer = malloc(sizeof(Tokenizer));
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

///<summary>
///Tokenizes the source string.
///</summary>
///<returns>
///A tokenizer output.
///</returns>
TokenizerOutput tokenize(Tokenizer* tokenizer)
{
	add_token(tokenizer, TK_START);
	int is_source_end = 0;
	while (!is_source_end)
	{
		tokenizer->kind = peek_tk(tokenizer, 0);
		switch (tokenizer->kind)
		{
			case TK_END:
				add_token(tokenizer);
				is_source_end = 1;
				break;
			case TK_WHITESPACE:
				advance(tokenizer);
				break;
			case TK_INVALID: case TK_IDENTIFIER: case TK_NUMBER:
				track_add_token(tokenizer);
				break;
		}
	}
	return create_tokenizer_output(tokenizer->tokens, tokenizer->token_count);
}

void advance(Tokenizer* tokenizer)
{
	tokenizer->cursor++;
}

/// <summary>
/// Adds the currently scanned token to the token pointer.
/// </summary>
void add_token(Tokenizer* tokenizer)
{
	tokenizer->tokens[tokenizer->token_count] = create_token(tokenizer->kind, tokenizer->source, tokenizer->beg, tokenizer->end);
	tokenizer->token_count++;
}

/// <summary>
/// Tracks the source string starting at the current cursor index and ending at the index when the peeked character is no longer the starting TokenKind.
/// </summary>
void track_add_token(Tokenizer* tokenizer)
{
	tokenizer->beg = tokenizer->cursor;
	while (peek_tk(tokenizer, 0) == tokenizer->kind)
		advance(tokenizer);
	tokenizer->end = tokenizer->cursor - 1;
	add_token(tokenizer);
}

///<returns>
///The character at the current cursor index of the source string.
///</returns>
char peek_c(Tokenizer* tokenizer, int offset)
{
	if (tokenizer->cursor + offset >= strlen(tokenizer->source))
		return '\0';
	return tokenizer->source[tokenizer->cursor + offset];
}

///<returns>
///The token kind of the currently peeked character of the source string.
///</returns>
TokenKind peek_tk(Tokenizer* tokenizer, int offset)
{
	return eval_tokenkind(peek_c(tokenizer, offset));
}

///<summary>
///Frees any memory allocated by the tokenizer.
///</summary>
void free_tokenizer(Tokenizer* tokenizer)
{
	free(tokenizer);
	tokenizer = NULL;
}

