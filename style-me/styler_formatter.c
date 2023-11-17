#include "styler_formatter.h"
#include "token_kind.h"
#include <stdlib.h>

/// <summary>
/// Returns a StylerBlock object created on the stack.
/// </summary>
StylerBlock create_styler_block(StyleType type, Token token) 
{
	StylerBlock block = { .type = type, .token = token};
	return block;
}

/// <summary>
/// Returns a  StylerBlockOutput containing all the formatted StylerBlock's generated from the given tokenizer output.
/// Must be deallocated by caller.
/// </summary>
StylerBlockOutput generate_styler_blocks(TokenizerOutput tokenizerOutput)
{
	Token* tokens = tokenizerOutput.tokens;
	StylerBlock* blocks = calloc(tokenizerOutput.count, sizeof(StylerBlock));
	int j = 0;
	int i = 0;
	while(i < tokenizerOutput.count)
	{
		if (tokens[i].kind == TK_ACCESS_MOD) 
		{
			int n1 = i + 1;
			int n2 = i + 2;
			int n3 = i + 3;
			if (tokens[n1].kind == TK_SCOPE_MOD)
			{
				if (tokens[n2].kind == TK_IDENTIFIER)
				{
					if (tokens[n3].kind == TK_IDENTIFIER)
					{
						blocks[j] = create_styler_block(ST_UNDEFINED, tokens[n3]);
						i = n3;
						j++;
					}
				}
			}
			else if (tokens[n1].kind == TK_IDENTIFIER)
			{
				if (tokens[n2].kind == TK_IDENTIFIER)
				{
					blocks[j] = create_styler_block(ST_UNDEFINED, tokens[n2]);
					i = n2;
					j++;
				}
			}
		}
		i++;
	}
	StylerBlockOutput blockOutput = { .blocks = blocks, .count = j };
	return blockOutput;
};

