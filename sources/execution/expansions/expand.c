#include "minislay.h"

//
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
//	return strndup(token + start + 1, tlen);
}

//
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
		return ("EOF");
	}
	return (NULL);
}

/*
static bool	get_merged(char **merged, char **temp, char **expanded)
{
	if (*temp)
	{
		*merged = ft_strjoin(*expanded, *temp);
		if (*merged)
		{
			free(*temp);
			*temp = NULL;
			free(*expanded);
			*expanded = *merged;
			return (true);
		}
		else
		{
			free(*temp);
			*temp = NULL;
			free(*expanded);
			*expanded = NULL;
		}
	}
	return (false);
}*/

/*
//Jouer avec un enum ici
bool	is_standard_key(char **value, char *key)
{
	int	index;

	index = 0;
	while (g_keys[index])
	{
		if (strcmp(key, g_keys[index]) == 0)
			*value = 	
	}
}*/

//We use this function to determine if the key is a standard key or an env/user
//defined key.
static bool	retrieve_keys_value(t_shel *minishell, char **key, char **value)
{
	if (**key == '$') 	
	{
	//	if (!is_standard_key(value, *key))
	//	{
			if (!find_key(minishell, value, *key + 1))
				return (false);
	//	}	
	}
	free(*key);
	*key = NULL;
	return true;
}

//
static bool	get_expanded(t_shel *minishell, t_tokn **token)
{
	int		jndex;
	int		index;
	char	*key;	
	char	*value;
	char	**expanded;

	key = NULL;
	value = NULL;
	expanded = (char **)malloc(sizeof(char *) * 100);
	if (expanded)
	{
		jndex = 0;
		index = 0;
		while ((*token)->value[index])
		{
			key = retrieve_expansions((*token)->value, &index);
			if (key)
			{
				if (!retrieve_keys_value(minishell, &key, &value))
					return false;
				value = strdup(value);
				if (!value)
					return (false);
				if (!strpbrk(value, " "))
				{
					expanded[jndex] = strtok_r(value, " ", &value);
					jndex++;
				}
				else
				{
					expanded[jndex] = value;
					while (strtok_r(value, " ", &value))
					{
						jndex++;
						expanded[jndex] = value;
					}
					jndex++;
				}
			}
		}
		if (!(*token)->value[index])
		{
			char	*temp = NULL;
			char	*merged = NULL;
			
			while (*expanded)
			{
				temp = merged;
				merged = ft_strjoin(temp, *expanded);
				if (!merged)
					return false;
				if (temp)
					free(temp);
				temp = NULL;
				expanded++;
			}
			printf("%s\n", merged);
		}
	}
	return false;
}
/*
	//	BELONGS TO PROCESS_KEY

				//if (!special_expansion(expansion))
				if (*key == '$')
				{
					if (find_key(minishell, &value, key + 1))
					{
						printf("%s\n", value);
					//	printf("%s\n", *expanded + index);
					//	free(value);
					}

						if (value)
							modify_expanded(expanded, value, index);

				}
			
			//	else if (strmcp(key, "EOF"))
				
				printf("%s	->	%s		@	%s\n", key, value, expanded + index);
			}
		}
	}
	return (false);
}*/

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn **list)
{
	while (*list)
	{
		if ((*list)->type & DOLL)
    	{
        	if (!get_expanded(minishell, list))
				return (false);
		}
		/*
		if ((*list)->type & STAR)
		{
			if (!globing(minishell, &(*list)->value))
				return (false);
    	}
		*/
        move_pointer(list);
    }
	return (!*list);
}
