/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:06:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/07 09:53:01 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	quote_removal_helper(char *token, char *removed)
{
	int		save;
	int		index;
	char	quote;

	save = 0;
	index = 0;
	quote = INIT;
	while (token[index])
	{
		if (!quote)
		{
			if (is_quote(token[index]))
				quote = token[index];
			else
				removed[save++] = token[index];
		}
		else
		{
			if (token[index] == quote)
				quote = INIT;
			else
				removed[save++] = token[index];
		}
		index++;
	}
}

//
static bool	quote_removal(t_tokn *list)
{
	int		tlen;
	char	*removed;

	while (list)
	{
		if (list->value)
		{
			tlen = strlen(list->value) + 1;
			removed = (char *)calloc(tlen, sizeof(char));
			if (!removed)
				return (false);
			quote_removal_helper(list->value, removed);
            free(list->value);
			list->value = removed;
		}
		move_pointer(&list);
	}
	return (true);
}

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
		free((*list)->value);		
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
	copy = *list;
    return (quote_removal(copy));
   // return (!copy);
}
