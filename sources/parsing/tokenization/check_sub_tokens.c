/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sub_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:38 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/13 18:42:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool	assess_dollar_sub_tokens(t_tokn **current)
{
	int		edgy_type;
	t_tokn	*edgy_boi;

	printf("inini\n");
	edgy_boi = NULL;
	edgy_type = (*current)->type;
	unset_state(&edgy_type, DOLL);
	if ((*current)->value && strlen((*current)->value) > 1)
	{
		edgy_boi = create_node((*current)->value + 1, edgy_type);
		if (edgy_boi)
		{
			edgy_boi->next = (*current)->next;
			printf("%s	%s	%s	%s\n", (*current)->value, (*current)->next->value, edgy_boi->value, edgy_boi->next->value);
			(*current)->value[1] = '\0';
			(*current)->next = edgy_boi;
			*current = edgy_boi;
		}
		return (edgy_boi != NULL);	
	}
	return (true);	
}

bool	check_sub_tokens(t_tokn **current)
{
	if (*current && (*current)->next)
	{
	printf("inini\n");
		if (is_state_active((*current)->type, DOLL))
		{
			if (is_state_active((*current)->next->type, DOLL))
			{
				if (assess_dollar_sub_tokens(current))
				{
					*current = (*current)->next;
					return (true);
				}
				*current = (*current)->next;
				return (false);
			}
		}
	}
	return ((*current)->next == NULL);
}
