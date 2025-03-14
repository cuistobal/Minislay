#include "minislay.h"

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
		return ("EOF");		//Needs to be modified.
	}
	return (NULL);
}

/*
//Jouer avec un enum ici
//We use this utility to asses if a key 
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
	if (*key)
	{
		if (**key != '$')	
			*value = strdup(*key);
		else
		{
		//	if (!is_standard_key(value, *key))
		//	{
				if (!find_key(minishell, value, *key + 1))
					return (false);
				*value = strdup(*value);
	//			printf("%s\n", *value);
		//	}	
		}	
//		printf("%s\n", *key);
//		printf("%s\n", *value);
		free(*key);
		*key = NULL;
		return (*value);
	}
	return (*key);
}

//
static bool	get_expanded(t_shel *minishell, t_tokn **token, char **value, int *index)
{
	char	*key;	
//	char	*temp;

	key = NULL;
//	temp = NULL;
//	while ((*token)->value[*index])
	if ((*token)->value[*index])
	{
		key = retrieve_expansions((*token)->value, index);
		if (key)
		{
			/*
			if (!retrieve_keys_value(minishell, &key, value))
				break ;
			*/
			if (!retrieve_keys_value(minishell, &key, value))
				return (false);
			return (true);
		}
	}
	return (!(*token)->value[*index]);
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

//Move to utils.
//We use this function to merge to arrays and free their original memory adress
static bool	get_merged(char **merged, char **temp, char **expanded)
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
	return (false);
}

/*
static bool	create_sub_list(t_tokn **current, char *merged, char *left)
{
	t_tokn	*new;
	t_tokn	*next;
	t_tokn	*save;

	save = (*current)->next;
	new = create_token_node(merged, WORD | DOLL);
	if (new)
	{
		*current = new;
		if (word_splitting(&new)
		{
			new->next = save;
			next = create_token_node(left, WORD | DOLL);
			if (next)
			{
				next->next = save;
				*current = next;
			}
		}
	}
}*/

//if multiple dollars, split the list into subtokens
static bool expand_no_quotes(t_shel *minishell, t_tokn **list)
{
	int		index;
	char	*temp;
	char	*value;
	char	*merged;

	index = 0;
	temp = NULL;
	value = NULL;
	merged = NULL;	
	if (is_state_active((*list)->type, DOLL))
	{
		while ((*list)->value[index])
		{
			if (!get_expanded(minishell, list, &value, &index))
				return (false);
			temp = merged;
			if (!get_merged(&merged, &temp, &value))
				return (false);
/*			if (!is_state_active((*list)->type, STAR))
			{
				if ((*list)->value[index])
				{
					printf("%s\n", (*list)->value + index);
				}
				if (!word_splitting(minishell, list, value))
					return (false);
			}*/
		}
		if (!is_state_active((*list)->type, STAR))
			return (!word_splitting(minishell, list, value));
		free((*list)->value);
		(*list)->value = merged;
	}
//	if (is_state_active((*list)->type, STAR))
//		globing();
	return (true);
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn **list)
{

//	Implement the delimiter retrieval module

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
