/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:32:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/15 14:11:27 by chrleroy         ###   ########.fr       */
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
	t_tokn	*current;

	if (*token)
	{
		index = 0;
		current = *token;
		if (current->value)
		{
			while (current->value[index] && current->value[index] != '=')
				index++;
			if (index > 0)
			{
				end = current->value + (index + 1);
				current->value[index] = '\0';
				current->type = WORD;
				current->next = create_node("=", EQUL);		
				if (current->next)
				{
					current = current->next;
					current ? printf("%s\n", current->value) : printf("NULL\n");
					current->next = create_node(end, WORD);
					if (current->next)
						return (true);
				}
			}
			else
				(*token)->type = WORD;
		}
	}
	return (false);
}
