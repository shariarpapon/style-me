#pragma once
#include "token.h"

///<summary>
///Output data of a tokenizing process.
///</summary>
typedef struct TokenizerOutput 
{
	Token* tokens;
	int count;
} TokenizerOutput;

TokenizerOutput create_tokenizer_output(Token* tokens, int count);
void free_tokenizer_output(TokenizerOutput output);