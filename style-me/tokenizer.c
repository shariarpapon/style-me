#include "TOKENIZER.h"
#include <string.h>
#include <stdio.h>


///<returns>
///A tokenizer pointer initialized with the source string.
///</returns>
Tokenizer* create_tokenizer(const char* source) 
{
	Tokenizer* tokenizer = malloc(sizeof(Tokenizer));
	tokenizer->tokens = calloc(strlen(source), sizeof(Token));
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
	int is_source_end = 0;
	while (!is_source_end)
	{
		tokenizer->kind = peek_tk(tokenizer, 0);
		switch (tokenizer->kind)
		{
			case TK_INVALID: 
			case TK_NUMBER:
			case TK_ARG_DELIMITER:
				track_add_token(tokenizer);
				break;
			case TK_IDENTIFIER: 
				track_add_identifier_or_keyword_token(tokenizer);
				break;
			case TK_END:
				is_source_end = 1;
				break;
			case TK_WHITESPACE:
				advance(tokenizer);
				break;
		}
	}
	
	const char* beg_tk_val = get_token_value(tokenizer->tokens[0]);
	if (strcmp(beg_tk_val, KEYWORD_begin) != 0)
	{
		perror("Cannot tokenize: source string does not define `begin`.");
		exit(EXIT_FAILURE);
	}

	const char* end_tk_val = get_token_value(tokenizer->tokens[tokenizer->token_count - 1]);
	if (strcmp(end_tk_val, KEYWORD_end) != 0)
	{
		perror("Cannot tokenize: source string does not define `end`.");
		exit(EXIT_FAILURE);
	}
	return create_tokenizer_output(tokenizer->tokens, tokenizer->token_count);
}

/// <summary>
/// Incremenets the cursor index of the source string.
/// </summary>
void advance(Tokenizer* tokenizer)
{
	tokenizer->cursor++;
}

/// <summary>
/// Adds the currently scanned token to the token pointer. The cursor index is not advanced and must be called explicitly.
/// </summary>
void add_token(Tokenizer* tokenizer)
{
	tokenizer->tokens[tokenizer->token_count] = create_token(tokenizer->kind, tokenizer->source, tokenizer->beg, tokenizer->end);
	tokenizer->token_count++;
}

/// <summary>
/// Tracks the source string starting at the current cursor index and ending at the index when the peeked character is no longer the starting TokenKind.
/// The cursor index is advanced until a different TokenKind is encnountered thus, advance() does not need to be called explicitly.
/// </summary>
void track_add_token(Tokenizer* tokenizer)
{
	tokenizer->beg = tokenizer->cursor;
	while (peek_tk(tokenizer, 0) == tokenizer->kind)
		advance(tokenizer);
	tokenizer->end = tokenizer->cursor - 1;
	add_token(tokenizer);
}

/// <summary>
/// Tracks and adds the current token as eitehr a identifier or a keyword if a match is found. 
/// The cursor index is advanced until a different TokenKind is encountered thus advance() does not need to be called explicitly.
/// </summary>
void track_add_identifier_or_keyword_token(Tokenizer* tokenizer) 
{
	tokenizer->beg = tokenizer->cursor;
	while (peek_tk(tokenizer, 0) == tokenizer->kind)
		advance(tokenizer);
	tokenizer->end = tokenizer->cursor - 1;
	char* value = get_token_value_raw(tokenizer->source, tokenizer->beg, tokenizer->end);
	if (is_keyword((const char*)value))
		tokenizer->kind = TK_KEYWORD;
	add_token(tokenizer);
}

/// <returns>
/// The character at the current cursor index of the source string.
/// </returns>
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

/// <returns>
///The next TokenKind that is not whitespace.
///</returns>
TokenKind peek_tk_next_nospace(Tokenizer* tokenizer)
{
	int offset_id = 1;
	TokenKind tk  = peek_tk(tokenizer, offset_id);
	while (tk == TK_WHITESPACE) 
	{
		++offset_id;
		tk = peek_tk(tokenizer, offset_id);
	}
	return tk;
}

///<summary>
///Frees any memory allocated by the tokenizer.
///</summary>
void free_tokenizer(Tokenizer* tokenizer)
{
	free(tokenizer);
	tokenizer = NULL;
}

