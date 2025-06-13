/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 17:37:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	tokenizer_helper(char *prev, char current)
{
	if ((is_iredir(*prev) || is_oredir(*prev)))
	{
		*prev = INIT;
		return (false);
	}
	if (is_paren(*prev) && is_paren(current) && current != *prev)
	{
		*prev = INIT;
		return (false);
	}
	return (true);
}

bool	valid_token_list(t_tokn *list)
{
	int		count;
	t_tokn	*current;

	count = 0;
	current = list;
	while (current)
	{
		move_pointer(&current);
		count++;
	}
	return (count > 1 || !valid_lexeme(list, HDOC, ARED));
}
