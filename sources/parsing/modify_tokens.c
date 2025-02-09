/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:32:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/09 15:44:01 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function in case we get a variable expansion within our 
static bool	split_token(t_tokn **input)
{
	int		index;
	t_tokn	*head;
	t_tokn	*tail;
	t_tokn	*current;

	index = 0;
	tail = NULL;
	head = NULL;
	current = NULL;
	while ((*input)->value[index])
	{
		if ((*input)->value[index] == '$')
	}
}

bool	assess_word_token(t_tokn **token)
{
	if ((*token))
	{
		if (strchr((*token)->value, '$') || strchr((*token)->value, '=') || strchr((*token)->value, '*'))
			return (split_token(token));
		return (true);
	}
	return (false);
}
