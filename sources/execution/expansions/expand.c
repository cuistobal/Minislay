#include "minislay.h"

//We need to implement the token split when dealing with weird stuff like
//"$PATH"'PATH'
//The code currently expands the '$PATH' variable iif it is preceeded with a
//double quoted or unquoted $ token.
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
static bool expand_no_quotes(t_shel *minishell, t_tokn **list, int *count)
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
	return (globing(list, CWD, count));
}

//Entry point of the expansion module
bool    expand(t_shel *minishell, t_tokn **list, int *count)
{
	while (*list)
	{
	//	if (is_state_active((*list)->type, DOLL) || is_state_active((*list)->type, STAR))
		if (((*list)->type & DOLL || (*list)->type & STAR))
		{
			if (!((*list)->type & DQTE) && (!expand_no_quotes(minishell, list, count)))
				return (false);
			else if ((*list)->type & DQTE && !expand_in_quotes(minishell, list))
				return (false);
		}
        move_pointer(list);
    }
    return (!*list);
}
