#include "minislay.h"


//Move to utils.
//We use this function to merge to arrays and free their original memory adress
static bool	get_merged(char **merged, char **temp, char **expanded)
{
	//*merged = ft_strjoin(*expanded, *temp);
	*merged = ft_strjoin(*temp, *expanded);
	if (*merged)
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
//		if (*expanded)
//            free(*expanded);
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

//Move to utils
/*
bool	insert_sub_list(t_tokn **list, char **new_elements)
{
	t_tokn	*new;
	t_tokn	*save;
	t_tokn	*next;
	int		index;
	
	if (*list)
	{
		save = *list;
		next = save->next;
	}
	if (new_elements)
	{
		index = 0;
		free((*list)->value);
		(*list)->value = new_elements[index]; 
		while (new_elements[index])
		{
			index++;
			if (new_elements[index])
			{
				new = create_token_node(new_elements[index], (*list)->type);
				if (!new)
					//memalloc failed
					return false;	
				(*list)->next = new;
				*list = new;
			}
		}
	//	(*list)->next = next;
		*list = next;
	}
	return true;
}*/

/*
//
static bool	get_globed(t_tokn **list, char *merged)
{
	if (merged)
	{
	//	free((*list)->value);
	//	(*list)->value = merged;
	}
	return (globing(list, CWD));
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
		}
       // free((*list)->value);
        (*list)->value = merged;
		if (!is_state_active((*list)->type, STAR))
			return (word_splitting(minishell, list));
		//	return (word_splitting(minishell, list, value));
	}
	return (globing(list, CWD));
	//return (get_globed(list, merged));
}

//Entry point of the expansion module
bool    expand(t_shel *minishell, t_tokn **list)
{
    //t_tokn  *next; 
//	Implement the delimiter retrieval module

    //next = NULL;
	while (*list)
	{
       // next = (*list)->next;
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
        //move_pointer(list);
    }
    return (!*list);
}
