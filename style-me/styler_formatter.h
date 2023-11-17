#pragma once
#include "tokenizer_output.h"

typedef enum StyleType
{
	ST_UNDEFINED = -1,
	ST_PUBLIC_VAR,
	ST_PRIVATE_VAR,
	ST_PROTECTED_VAR,
	ST_INTERNAL_VAR,
	ST_PUBLIC_PROP,
	ST_PRIVATE_PROP,
	ST_PROTECTED_PROP,
	ST_INTERNAL_PROP
} StyleType;

typedef struct StylerBlock
{
	StyleType type;
	Token token;
} StylerBlock;

typedef struct StylerBlockOutput 
{
	StylerBlock* blocks;
	int count;
} StylerBlockOutput;

StylerBlock create_styler_block(StyleType type, Token token);
StylerBlockOutput generate_styler_blocks(TokenizerOutput tokenizerOutput);


