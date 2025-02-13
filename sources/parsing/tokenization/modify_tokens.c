/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:32:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/13 13:30:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs to bew splited in 2 functions

//Here, we split the assignation token around the '=' that defines it.
//The original *token node now represents the portion before the '=', and we
//create 2 new nodes. The first one holds the assignation '=' signe, while the
//second holds the second part of the assignation.
bool	split_assignation_token(t_tokn **token)
{
	char	*end;
	int		index;

	if (*token)
	{
		index = 0;
		if ((*token)->value)
		{
			while ((*token)->value[index])
			{
				if ((*token)->value[index] == '=')
					break ;
				index++;
			}
			end = (*token)->value + (index + 1);
			(*token)->value[index] = '\0';
			(*token)->type = WORD;
		}
		(*token)->next = create_node("=", EQUL);
		if ((*token)->next)
		{
			*token = (*token)->next;
			(*token)->next = create_node(end, WORD);
			if ((*token)->next)
				return (*token = (*token)->next, true);
		}
	}
	return (false);
}
