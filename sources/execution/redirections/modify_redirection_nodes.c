/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_redirection_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:47:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 14:22:55 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	set_state_helper(t_tokn *copy)
{
	if (is_state_active(copy->type, HDOC))
		set_state(&copy->next->type, HDOC);
	if (is_state_active(copy->type, IRED))
		set_state(&copy->next->type, IRED);
	if (is_state_active(copy->type, ORED))
		set_state(&copy->next->type, ORED);
	if (is_state_active(copy->type, ARED))
		set_state(&copy->next->type, ARED);
}

//
void	modify_redirections_nodes(t_tokn **source)
{
	t_tokn	*prev;
	t_tokn	*next;
	t_tokn	*copy;

	prev = NULL;
	copy = *source;
	while (copy)
	{
		next = copy->next;
		if (valid_lexeme(copy, HDOC, ARED))
		{
			set_state_helper(copy);
			if (!prev)
			{
				free((*source)->value);
				free(*source);
				*source = next;
				copy = *source;
			}
			else
			{
				prev->next = next;
				free(copy->value);
				free(copy);
				copy = next;
			}
		}
		prev = copy;
		move_pointer(&copy);
	}
}
