/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:06:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 19:00:03 by chrleroy         ###   ########.fr       */
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

//
static bool	expand_no_quotes_helper(t_shell *m, t_tokn **l, int *i, char **r)
{
	char	*temp;
	char	*value;

	temp = NULL;
	value = NULL;
	if (!get_expanded(m, (*l)->value, &value, i))
		return ((*i)++, free(value), true);
	temp = *r;
	*r = get_merged(r, &temp, &value);
	if (!*r)
		return (false);
	if (*i > (int)ft_strlen((*l)->value))
	{
		value = ft_strdup((*l)->value + (ft_strlen((*l)->value) - 1));
		if (!value)
			return (false);
		temp = *r;
		*r = get_merged(r, &temp, &value);
		if (!*r)
			return (false);
	}
	return (true);
}

//
static bool	expand_no_quotes(t_shell *minishell, t_tokn **list, int *count)
{
	int		tlen;
	int		index;
	char	*expanded;

	index = 0;
	expanded = NULL;
	if (is_state_active((*list)->type, DOLL))
	{
		tlen = ft_strlen((*list)->value);
		while ((*list)->value[index])
		{
			if (!expand_no_quotes_helper(minishell, list, &index, &expanded))
				return (free(expanded), false);
			if (index > tlen)
				break ;
		}
		free((*list)->value);
		(*list)->value = expanded;
		if (!is_state_active((*list)->type, STAR))
			return (word_splitting(minishell, list));
	}
	return (globing(list, CWD, count));
}

//Entry point of the expansion module
bool	expand(t_shell *minishell, t_tokn **list)
{
	int		count;
	t_tokn	*copy;

	count = 0;
	copy = *list;
	while (copy)
	{
		if ((copy->type & DOLL || copy->type & STAR) && (!(copy->type & HDOC)))
		{
			if (!((copy)->type & DQTE) && (!expand_no_quotes(minishell, \
							&copy, &count)))
				return (false);
			else if ((copy)->type & DQTE && !expand_in_quotes(minishell, \
						&copy))
				return (false);
		}
		while (count-- > 0)
			move_pointer(&copy);
		move_pointer(&copy);
	}
	copy = *list;
	return (quote_removal(copy));
}
