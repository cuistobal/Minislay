/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_redirection_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:47:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 10:23:27 by chrleroy         ###   ########.fr       */
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
static void	pointer_update_helper(t_tokn **copy, t_tokn **prev, \
		t_tokn **source, t_tokn *next)
{
	if (!*prev)
	{
		free((*source)->value);
		(*source)->value = NULL;
		free(*source);
		*source = next;
		*copy = *source;
	}
	else
	{
		(*prev)->next = next;
 		free((*copy)->value);
		(*copy)->value = NULL;
		free(*copy);
 		*copy = next;
	}
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
			pointer_update_helper(&copy, &prev, source, next);
		}
		prev = copy;
		move_pointer(&copy);
	}
}
