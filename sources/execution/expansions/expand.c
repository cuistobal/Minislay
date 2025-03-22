#include "minislay.h"

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
			if (get_expanded(minishell, (*list)->value, &value, &index))
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
			if (!get_expanded(minishell, (*list)->value, &value, &index))
				return (false);
			temp = merged;
			if (!get_merged(&merged, &temp, &value))
				return (false);
		}
        (*list)->value = merged;
		if (!is_state_active((*list)->type, STAR))
			return (word_splitting(minishell, list));
	}
	return (globing(list, CWD));
}

//Entry point of the expansion module
bool    expand(t_shel *minishell, t_tokn **list)
{
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
