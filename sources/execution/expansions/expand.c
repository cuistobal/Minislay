#include "minislay.h"

//Expansion found ? realloc
//
//If star and no pattern match -> pattern stays unexpended EXPECT for $Expansions
//
//This is the main expansion function. Identifies $ && * elements within the
//token's value and performs variable expansion.
bool    expand(t_shel *minishell, t_tokn *token)
{
	char	*key;
	char	*value;
	char	*expanded;
	char	**expnd_tab;

	if (minishell)
	{
		if (token)
		{
			value = token->value;
			while (*value)
			{
				key = strpbrk(value, EXPANDS);
				if (key)
				{
					
				}
				if (*value == '$')
				{
					key = 	
				}
				
			}
		}
		return (token);
	}
	return (minishell);
}

//
static bool	handle_dollars(char *value, int *index, bool *dollar, int *len)
{
	int		klen;
	char	*key;

	key = NULL;
	klen = *index;
	if (value)
	{
		if (!dollar)
		{
			dollar = true;
			while (value[*index])
			{
				if (is_space(value[*index])	|| strchr(EXPANDS, value[*index]))
					break;
				(*index)++;
			}
			key = strndup(value + klen, *index - klen);
			if (key)
				return (printf("%s\n", key), free(key), true);
		}
		else
		{
			dollar = false;
				
		}
	}
	return (false);
}

//
static bool	handle_stars(char *value, int *index, bool *dollar, int *len)
{
	if (value)
	{

	}
	return (false);
}

//
bool	find_expansions_within_token(char *value, int *len)
{
	int		index;
	bool	dollar;
	char	quotes;

	dollar = false;
	if (value)
	{
		index = 0;
		while (value[index])
		{
			if (value[index] == '$')
				handle_dollars(value, &index, &dollar, len);
			if (value[index] == '*')
				handle_stars(value, &index, &dollar, len);
			index++;
		}
	}
}
