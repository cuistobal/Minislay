#include "minislay.h"

//Checks the validity of the key
static bool	valid_variable(char *key)
{
	if (key)
	{
		if (isalpha(*key) || *key == '_')
		{
			key++;
			while (*key)
			{
				if (!isalnum(*key) && *key != '_')
					break ;
				key++;
			}
		}
	}
	return (!*key);
}

//If one assignation is invalid, it's considered a command and rest of the 
//assignations list becomes an argument.
bool	check_keys_validity(t_tokn *assignations)
{
	if (assignations)
	{
		while (assignations)
		{
			if (!valid_variable(assignations->value))
			{
				assignations->type = WORD;
				/*
				move_pointer(&assignations);
				while (assignations)
				{
					assignations->type = WORD;
					move_pointer(&assignations);
				}
				return (false);*/
			}
			return (true);
		}
	}
}
