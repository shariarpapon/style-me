#pragma once
#include "TOKENIZER.h"
#include <stdio.h>

int main()
{
	//Test the tokenizer
	const char* test_source = "begin\nmake foo\nprocedure input(age, name) output(int) \nend";
	printf("SOURCE CODE\n----------------\n");
	printf("%s%s", test_source,"\n-------------------------------------\n\n");

	Tokenizer* tokenizer = create_tokenizer(test_source);
	TokenizerOutput output = tokenize(tokenizer);
	for (int i = 0; i < output.count; ++i)
	{
		const char* kind_str = tokenkind_to_str(output.tokens[i].kind);
		const char* token_val = get_token_value(output.tokens[i]);
		printf("%s  %s\n", kind_str, token_val);
	}
	free_tokenizer(tokenizer);
	free_tokenizer_output(output);
	return 0;
}