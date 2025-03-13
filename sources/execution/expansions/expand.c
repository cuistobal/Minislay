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
			//printf("%s\n", *value);
	//	}	
	}
	free(*key);
	*key = NULL;
	return (true);
}

//
static bool	get_expanded(t_shel *minishell, t_tokn **token, char **value, int *index)
{
//	int		jndex;
//	int		index;
	char	*key;	
//	char	**expanded;

	key = NULL;
//	value = NULL;
//	expanded = (char **)malloc(sizeof(char *) * 100);
//	if (expanded)
	{
//		jndex = 0;
//		index = 0;
		while ((*token)->value[*index])
		{
		//	key = retrieve_expansions((*token)->value, &index);
			key = retrieve_expansions((*token)->value, index);
			if (key)
			{
				if (retrieve_keys_value(minishell, &key, value))
					*value = strdup(*value);
				free (key);
				return (*value);
			}
		}
	}
	return (false);
}

//
static bool	expand_in_quotes(t_shel *minishell, t_tokn **list)
{
	(void)minishell;
	if (is_state_active((*list)->type, DOLL))
	{
//   		if (!get_expanded(minishell, list))
			return (false);
	}
	return (true);
}

static bool	expand_for_globing(char *token)
{
//	int		index;
//	char	*expanded;

//	expanded = NULL;
	if (token)
	{
//		index = 0;
//		while (token[index])
//		{
		return true;			
//		}
	}
	return false;
}

//if multiple dollars, split the list into subtokens
static bool expand_no_quotes(t_shel *minishell, t_tokn **list)
{
	int		index;
	char	*value;
	char	*merged;

	index = 0;
	value = NULL;
	merged = NULL;	
	if (is_state_active((*list)->type, STAR))
		return (expand_for_globing((*list)->value));
	else if (is_state_active((*list)->type, DOLL))
	{
		while ((*list)->value[index])
		{
			if (!get_expanded(minishell, list, &value, &index))
				return (false);
			
// DEV LE MODULE PLS
// *
			char	*temp = merged;
			merged = ft_strjoin(temp, value);
			free(temp);
			temp = NULL;
			free(value);
			value = NULL;
			if (!merged)
				return false;
			printf("value	->	%s\n", merged);
		
		}
		free((*list)->value);
		(*list)->value = merged;
	}
	return (true);
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn **list)
{
	while (*list)
	{
		if (!is_state_active((*list)->type, DQTE))
		{
			if (!expand_no_quotes(minishell, list))
				return (false);
		}
		else
		{
			if (!expand_in_quotes(minishell, list))
				return (false);
		}

		//	*OLD
		//	if (is_state_active((*list)->type, DOLL))
    	//	{
        //		if (!get_expanded(minishell, list))
		//			return (false);
		//	}
	
        move_pointer(list);
    }
	return (!*list);
}
