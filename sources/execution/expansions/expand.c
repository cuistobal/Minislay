/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:06:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 09:02:46 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We need to implement the token split when dealing with weird stuff like
//"$PATH"'PATH'
//The code currently expands the '$PATH' variable iif it is preceeded with a
//double quoted or unquoted $ token.
//
static bool	expand_in_quotes(t_shell *minishell, t_tokn **list)
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
static bool expand_no_quotes(t_shell *minishell, t_tokn **list, int *count)
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
	//	free((*list)->value);		
        (*list)->value = merged;
		if (!is_state_active((*list)->type, STAR))
			return (word_splitting(minishell, list));
	}
	return (globing(list, CWD, count));
}

//Entry point of the expansion module
bool    expand(t_shell *minishell, t_tokn **list)
{
	int		count;
	t_tokn	*copy;

	count = 0;
	copy = *list;
	while (copy)
	{
		if (copy->type & DOLL || copy->type & STAR)
		{
			if (!((copy)->type & DQTE) && (!expand_no_quotes(minishell, &copy, &count)))
				return (false);
			else if ((copy)->type & DQTE && !expand_in_quotes(minishell, &copy))
				return (false);
		}
        move_pointer(&copy);
    }
    return (!copy);
}
