/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:30:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 10:38:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
t_tokn	*copy_token(t_tokn *source)
{
	t_tokn	*new;

	new = NULL;
	if (!source)
		return (NULL);
	new = malloc(sizeof(t_tokn));
	if (!new)
		return (NULL);
	new->value = strdup(source->value);
	new->type = source->type;
	new->next = source->next;
	return (new);
}

//I USED TERNARIES ON LEETCODE AND IT WAS FCKING READABLE
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

//I HONESTLY FCKING HATE THE NORM
static void	modify_pointers(t_tokn **list, t_tokn **p, t_tokn **n, t_tokn **cur)
{
	if (!*p)
        *list = *n;
	else
        (*p)->next = *n;

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
			current->next = NULL;
			current = prev;
        }
		append_pointers_values(list, &current, &prev);
    }
    return (subhead);
}
