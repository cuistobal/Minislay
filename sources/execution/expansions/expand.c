#include "minislay.h"


//Move to utils.
//We use this function to merge to arrays and free their original memory adress
static bool	get_merged(char **merged, char **temp, char **expanded)
{
	*merged = ft_strjoin(*expanded, *temp);
	if (*merged)
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		free(*expanded);
		*expanded = *merged;
		return (true);
	}
	else
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		free(*expanded);
		*expanded = NULL;
	}
	return (false);
}

//
static bool	expand_in_quotes(t_shel *minishell, t_tokn **list)
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
			if (get_expanded(minishell, list, &value, &index))
			{	
				temp = merged;
				if (!get_merged(&merged, &temp, &value))
					break ;
			}
		}
		return (!(*list)->value[index]);
	}
	return (true);
}

//
static bool	get_globed(t_shel *minishell, t_tokn **list, char *merged)
{
	int		count;
	char	**globed;

	if (minishell)
		printf("\n");	
	count = 0;
	globed = NULL;
	free((*list)->value);
	(*list)->value = merged;
	globed = globing(merged, "." , &count);
	if (globed)
	{
		if (count > 1)
		{
			while (*globed)
			{
				printf("globed -> %s\n", *globed);
				globed++;
			}
			//create_sub_list();
		}
		else
		{
			free((*list)->value);
			(*list)->value = merged;
		}
	}
	return (globed);
}

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
		}
		if (is_state_active((*list)->type, STAR))
			return (get_globed(minishell, list, merged));
		return (word_splitting(minishell, list, value));
	}
	index = 1;
	char	**globed = globing((*list)->value, ".", &index);
	while (*globed)
	{
		printf("%s\n", *globed);
		globed++;
	}
//	return (globing((*list)->value, ".", &index));
	return (true);
}

//Entry point of the expansion module
bool    expand(t_shel *minishell, t_tokn **list)
{

//	Implement the delimiter retrieval module

	while (*list)
	{
		if (is_state_active((*list)->type, DOLL) || is_state_active((*list)->type, STAR))
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
		}
	
        move_pointer(list);
    }
	return (!*list);
}
