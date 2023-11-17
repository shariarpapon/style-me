#pragma once
#include "tokenizer.h"
#include "tk_enum_conversion.h"
#include "string_utils.h"
#include "styler_formatter.h"
#include <stdio.h>

#define true 1
#define false 0

#define PRINT_SORUCE false
#define PRINT_TOKENIZED_OUTPUT true

#define NUM_TK_FILTERS 3
static TokenKind tk_filter[NUM_TK_FILTERS] = { TK_ACCESS_MOD, TK_SCOPE_MOD, TK_IDENTIFIER };

int main()
{
	const char* test_filepath = "testsource.txt";
	const char* test_source = read_source_file(test_filepath);

	if (PRINT_SORUCE) 
	{
		printf("%s%s%s","-------------------\nSOURCE CODE\n-------------------\n", test_source, "\n");
	}

	if (PRINT_TOKENIZED_OUTPUT)
	{
		printf("-------------------\nTOKENIZED OUTPUT\n-------------------\n");
		Tokenizer* tokenizer = create_tokenizer(test_source);
		TokenizerOutput tknOutput = tokenize(tokenizer);
		for (int i = 0; i < tknOutput.count; ++i)
		{
			for(int j = 0; j < NUM_TK_FILTERS; j++)
				if (tknOutput.tokens[i].kind == tk_filter[j]) 
				{
					printf("%s  %s\n", tk_to_string(tknOutput.tokens[i].kind), get_token_value(tknOutput.tokens[i]));
					break;
				}
		}
		printf("\n\n");
		StylerBlockOutput blockOutput = generate_styler_blocks(tknOutput);
		for (int i = 0; i < blockOutput.count; i++) 
		{
			StylerBlock b = blockOutput.blocks[i];
			int _t = (int)b.type;
			printf("%d  %s\n", _t, get_token_value(b.token));
		}
		
		free(blockOutput.blocks);
		free_tokenizer(tokenizer);
		free_tokenizer_output(tknOutput);
	}

	return 0;
}