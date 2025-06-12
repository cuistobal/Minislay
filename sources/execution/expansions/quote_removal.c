/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:30:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:18:42 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	quote_removal_helper(char *token, char *removed)
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
bool	quote_removal(t_tokn *list)
{
	int		tlen;
	char	*removed;

	while (list)
	{
		if (list->value && *list->value)
		{
			tlen = ft_strlen(list->value) + 1;
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
