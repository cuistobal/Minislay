#include "minislay.h"

//Expansion found ? realloc

static bool handle_regular_expansions()
{

}

static bool handle_dqte_expansions()
{
	
}

//If star and no pattern match -> pattern stays unexpended EXPECT for $Expansions



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

static bool	handle_dollars(char *value, bool *dollar)
{
	if (value)
	{
		if (!dollar)
			dollar = true;
		else
		{
			dollar = false;
			split[] = split[ - 1] 
		}
	}
	return (false);
}

static bool	handle_stars(char *value)
{
	if (value)
	{

	}
	return (false);
}

bool	find_expansions_within_token(char *value)
{
	int		index;
	bool	dollar;

	dollar = false;
	if (value)
	{
		index = 0;
		while (value[index])
		{
			if (value[index] == '$')
			{
				if (!dollar)
					dollar = true;
				else
				{
					dollar = false;
					
				}
			}
			if (value[index] == '*')
			{

			}
		}
	}
}
