/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:30:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/23 16:19:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	append_pointers_values(t_tokn **list, t_tokn **current, t_tokn **prev)
{
	if (!*current)
		*current = *list;
	else
	{
		*prev = *current;
		*current = (*current)->next;
	}
}

//
static void	modify_pointers(t_tokn **list, t_tokn **p, t_tokn **n, t_tokn **cur)
{
	if (!*p)
        *list = *n;
	else
    {
        (*p)->next = *n;
		(*cur)->next = NULL;
    }

}

//This utility removes all nodes where ttype is an active state, and put them
//in a new list that is returned by the function.
t_tokn	*create_token_sub_list(t_tokn **list, int ttype)
{
    t_tokn	*prev;
    t_tokn	*next;
    t_tokn	*current;
	t_tokn	*subhead;
	t_tokn	*subtail;

	prev = NULL;
	next = NULL;
	subtail = NULL;
	subhead = NULL;
	current = *list;
    while (current)
    {
        next = current->next;
        if (is_state_active(current->type, ttype))
        {
			modify_pointers(list, &prev, &next, &current);
			append_token_list(&subhead, &subtail, current);
			current = prev;
			//printf("prev %p\n", prev);
        }
		append_pointers_values(list, &current, &prev);
    }
    return (subhead);
}
