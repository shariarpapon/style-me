#include "TOKENIZER_OUTPUT.h"
#include <stdlib.h>

TokenizerOutput* create_tokenizer_output(Token* tokens, int count) 
{
	TokenizerOutput* output = malloc(sizeof(TokenizerOutput));
	output->tokens = tokens;
	output->count = count;
	return output;
}