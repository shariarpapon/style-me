#include "TOKENIZER_OUTPUT.h"
#include <stdlib.h>

///<returns>
///A TokenizerOutput with the given data.
///</returns>
TokenizerOutput create_tokenizer_output(Token* tokens, int count) 
{
	TokenizerOutput output = { .tokens = tokens, .count = count };
	return output;
}

///<summary>
///Frees any memory allocated by the given TokenizerOutput. 
///</summary>
void free_tokenizer_output(TokenizerOutput output)
{
	free((void*)output.tokens);
	output.tokens = NULL;
};
