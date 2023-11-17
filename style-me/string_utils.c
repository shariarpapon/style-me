#pragma once
#include "string_utils.h"

///<summary>
///Returns a substring from the source string of length [len] and starting at [index = beg]. 
/// Memory leaks go crazy.
///</summary>
const char* get_substr_with_len(const char* source, int beg, int len)
{
	char* output = (char*)calloc(len, sizeof(char));
	for (int i = 0; i < len; i++)
		output[i] = source[beg + i];
	output[len] = '\0';
	return (const char*)output;
}

///<summary>
///Returns a substring from the source string from [index = beg] to [index = end]. 
/// Memory leaks go crazy.
///</summary>
const char* get_substr_fromto(const char* source, int beg, int end)
{
	int len = end - beg + 1;
	return get_substr_with_len(source, beg, len);
}