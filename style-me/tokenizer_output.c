#include "TOKENIZER_OUTPUT.h"
#include <stdlib.h>

TokenizerOutput create_tokenizer_output(Token* tokens, int count) 
{
	TokenizerOutput output = { .tokens = tokens, .count = count };
	return output;
}

void free_tokenizer_output(TokenizerOutput output)
{
	free((void*)output.tokens);
	output.tokens = NULL;
}
