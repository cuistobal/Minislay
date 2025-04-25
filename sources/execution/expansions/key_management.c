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

static inline void	quote_state(char current, char *quote, bool *sqte)
{
	if (is_quote(current))
	{
		if (!*quote)
		{
			*quote = current;
			*sqte = *quote == '\'';
		}
		else if (*quote == current)
		{
			*quote = INIT;
			*sqte = *quote == '\'';
		}
	}

}
//We use this utility to discriminate keys and non keys within the current token
//string.
//This is where we should implement the SQTE DQTE discrimination. POssibly using
//a stack approach where we pile the quotes if peek() == token[index].
static char	*retrieve_expansions(char *token, int *index)
{
	bool		sqte;
	int			start;
	static char	quote;

	sqte = false;
//	quote = INIT;
	start = *index;
	if (*index == 0)
		quote = INIT;
	if (token[*index])
	{
		while (token[*index])
		{
			// quote_handler()	This smol util needs implemetantion.
			// 					Note that a similar code snippet is implemented
			// 					in tokenizer.c
		//	printf("@%d	->	bool = %d, token[*index] = %c, quote = %c\n", *index, sqte, token[*index], quote);		
			/*
			if (is_quote(token[*index]))
			{
				if (!quote)
				{
					quote = token[*index];
					sqte = quote == '\'';
				}
				else if (quote == token[*index])
				{
					quote = INIT;
					sqte = quote == '\'';
				}
			}
			*/
			quote_state(token[*index], &quote, &sqte);
		//	else if (token[*index] == '$' && !sqte)
			if (token[*index] == '$' && !sqte)
			{
				printf("%s\n", token + *index);
				if (*index == start)
					return (extract_key(token, index, start));
				//index modification here ?
				return (strndup(token + start, *index - start));
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
		return (*value);
	}
	return (*key);
}

//
bool	get_expanded(t_shel *minishell, char *token, char **value, int *index)
{
	char	*key;

	key = NULL;
	if (token && token[*index])
	{
		key = retrieve_expansions(token, index);
		if (key)
		{
			if (!retrieve_keys_value(minishell, key, value))
				*value = "";
			return (true);
		}
	}
	return (!token[*index]);
}

/*
bool	get_expanded(t_shel *minishell, char *token, char **value, int *index)
{
	char	*key;

	key = NULL;
	if (!token || !token[*index])
		return (false);
	key = retrieve_expansions(token, index);
	if (!key)
		return (false);
	if (retrieve_keys_value(minishell, key, value))
		return (true);	

	*value = "";
	return (true);
}
*/
