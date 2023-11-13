#define _CRT_SECURE_NO_DEPRECATE
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
///A tokenizer output which contains the token pointer and the number of tokens.
///</returns>
TokenizerOutput tokenize(Tokenizer* tokenizer)
{
	int is_source_end = 0;
	while (!is_source_end)
	{
		tokenizer->kind = peek_tk(tokenizer, 0);
		switch (tokenizer->kind)
		{
			case TK_WHITESPACE:
				advance(tokenizer);
				break;
			case TK_INVALID:
				notrack_add_token(tokenizer);
				break;
			case TK_IDENTIFIER:
				track_add_identifier_token(tokenizer);
				break;
			case TK_NUMBER:
				track_add_token(tokenizer);
				break;
			case TK_END:
				is_source_end = 1;
				break;
		}
	}
	return create_tokenizer_output(tokenizer->tokens, tokenizer->token_count);
}

///<returns>
///The complete source string scanned from the given filepath.
///</returns>
const char* read_source_file(const char* path)
{
	FILE* file;
	file = fopen(path, "r");
	size_t char_count = 0;
	while (!feof(file)) 
	{
		char_count++;
		fgetc(file);
	}
	fseek(file, 0, SEEK_SET);
	char* str = calloc(char_count, sizeof(char));
	fread(str, 1, char_count, file);
	str[char_count] = '\0';
	fclose(file);
	return str;
}

/// <summary>
/// Incremenets the cursor index of the source string.
/// </summary>
void advance(Tokenizer* tokenizer)
{
	tokenizer->cursor++;
}

/// <summary>
/// Adds a token with the currently tracked tokenizer data.
/// </summary>
void add_current_token(Tokenizer* tokenizer)
{
	Token cur_token = create_token(tokenizer->kind, tokenizer->source, tokenizer->beg, tokenizer->end);
	add_token(tokenizer, cur_token);
}

/// <summary>
/// Adds the given token to the token pointer.
/// </summary>
void add_token(Tokenizer* tokenizer, Token token)
{
	tokenizer->tokens[tokenizer->token_count] = token;
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
	add_current_token(tokenizer);
}

/// <summary>
/// Adds a token for the single character and does not track farther for a whole string. The cursor index is advanced after adding the token thus,
/// advance() does not need to be called explicitly.
/// </summary>
void notrack_add_token(Tokenizer* tokenizer)
{
	tokenizer->beg = tokenizer->cursor;
	tokenizer->end = tokenizer->beg;
	add_current_token(tokenizer);
	advance(tokenizer);
}

/// <summary>
/// Tracks and adds the current token as eitehr a identifier or a keyword if a match is found. 
/// The cursor index is advanced until a different TokenKind is encountered thus, advance() does not need to be called explicitly.
/// </summary>
void track_add_identifier_token(Tokenizer* tokenizer) 
{
	tokenizer->beg = tokenizer->cursor;
	while (peek_tk(tokenizer, 0) == tokenizer->kind)
		advance(tokenizer);
	tokenizer->end = tokenizer->cursor - 1;
	char* value = get_token_value_raw(tokenizer->source, tokenizer->beg, tokenizer->end);
	if (is_access_mod((const char*)value))
		tokenizer->kind = TK_ACCESS_MOD;
	else if (is_scope_mod((const char*)value))
		tokenizer->kind = TK_SCOPE_MOD;
	else 
		tokenizer->kind = TK_IDENTIFIER;
	add_current_token(tokenizer);
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
	free((void*)tokenizer);
	tokenizer = NULL;
}

