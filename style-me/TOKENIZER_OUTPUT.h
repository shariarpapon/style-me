#pragma once
#include "TOKEN.h"

typedef struct TokenizerOutput 
{
	Token* tokens;
	int count;
} TokenizerOutput;

TokenizerOutput* create_tokenizer_output(Token* tokens, int count);