#include "minislay.h"

static const char *g_keys[DKCT] = {DSTR, DARO, DHAS, DEXT, DHYP, DPID, DCID, DNME, DLST, DIFS};

//
static bool	is_standard_key(t_shel *minishell, char **value, char *key)
{
	int	index;

	index = 0;
	while (index < DKCT)
	{
		if (strcmp(key, g_keys[index]) == 0)
		{
			*value = minishell->special[index];
			break ;
		}
		index++;
	}	
	return (index < DKCT);
}


//We use this utility to extract the key within the current token string.
static char	*extract_key(char *token, int *index, int start)
{
	int	tlen;

	tlen = 0;
	while (token[*index])
	{
		(*index)++;
		if (!isalnum(token[*index]) && token[*index] != '_')
		{
			if (tlen == 0)
			{
				if (token[*index] == '$' || token[*index] == '?')
				{
					tlen++;	
					(*index)++;
				}
				return strndup(token + start, tlen + 1);
			}
			break ;
		}
		tlen++;	
	}
	return strndup(token + start, tlen + 1);
}

//We use this utility to discriminate keys and non keys within the current token
//string.
static char	*retrieve_expansions(char *token, int *index)
{
	int		start;

	start = *index;
	if (token[*index])
	{
		while (token[*index])
		{
			if (token[*index] == '$')
			{
				if (*index == start)
					return extract_key(token, index, start);
				return strndup(token + start, *index - start);	
			}
			(*index)++;
		}
		return (token + start);		//Needs to be modified.
	}
	return (NULL);
}

//We use this function to determine if the key is a standard key or an env/user
//defined key.
static bool	retrieve_keys_value(t_shel *minishell, char *key, char **value)
{
	if (key)
	{
		if (*key != '$')
			*value = strdup(key);
		else
		{
			if (!is_standard_key(minishell, value, key))
			{
				if (!find_key(minishell, value, key + 1))
					return (false);
			}
			*value = strdup(*value);
		}
		/*
		free(*key);
		*key = NULL;
		*/
		return (*value);
	}
	return (*key);
}

//
bool	get_expanded(t_shel *minishell, char **token, char **value, int *index)
{
	char	*key;

	key = NULL;
	if (*token[*index])
	{
		key = retrieve_expansions(*token, index);
		if (key)
		{
			if (retrieve_keys_value(minishell, key, value))
			{
				return (true);	
			}
			//return (retrieve_keys_value(minishell, &key, value));
		*value = strdup(key);
		//	(*token)->value + *index;
		return (true);
		}
	}
	return (!*token[*index]);
}
