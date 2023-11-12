#pragma once
#include "TOKENIZER.h"
#include <stdio.h>

#define PRINT_SORUCE 1
#define PRINT_TOKENIZED_OUTPUT 1

int main()
{
	const char* test_source_file = "testsource.txt";
	const char* test_source = read_source_file(test_source_file);

	if (PRINT_SORUCE) 
	{
		printf("%s%s%s","-------------------\nSOURCE CODE\n-------------------\n", test_source, "\n");
	}

	if (PRINT_TOKENIZED_OUTPUT)
	{
		printf("-------------------\nTOKENIZED OUTPUT\n-------------------\n");
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
	}

	return 0;
}