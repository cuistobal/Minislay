/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:32:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/09 16:30:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function in case we get a variable expansion within our 
static bool	split_token(t_tokn **token, char *sub_token)
{
	t_tokn	*new;
	t_tokn	*next;

	new = create_node(sub_token);
	if (new)
	{
		new = (*token)->next;
		(*token)->next = new;
		new->next = next;
	}
	return (new != NULL);
}

//Used to asses if a " token needs further spliting for interpretation, 
//assignement and expenasion during the execution phase.
bool	assess_word_token(t_tokn **token)
{
	char	*sub_token;

	if ((*token))
	{
		if (strchr((*token)->value, '$') || strchr((*token)->value, '=') || strchr((*token)->value, '*'))
		{
			sub_token = strpbrk((*token)->value, IAE);
			return (split_token(token, sub_token));
		}
	}
	return (false);
}
