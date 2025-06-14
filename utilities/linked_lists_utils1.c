/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:30:31 by chrleroy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 12:27:45 by chrleroy         ###   ########.fr       */
=======
/*   Updated: 2025/06/12 17:16:37 by ynyamets         ###   ########.fr       */
>>>>>>> feat/add_libft
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

t_tokn	*copy_token(t_tokn *source)
{
	t_tokn	*new;

	new = NULL;
	if (!source)
		return (NULL);
	new = malloc(sizeof(t_tokn));
	if (!new)
		return (NULL);
	new->value = ft_strdup(source->value);
	new->type = source->type;
	new->next = source->next;
	return (new);
}

static void	append_pointers_values(
	t_tokn **list, t_tokn **current, t_tokn **prev)
{
	if (!*current)
		*current = *list;
	else
	{
		*prev = *current;
		*current = (*current)->next;
	}
}

static void	modify_pointers(t_tokn **list, t_tokn **p, t_tokn **n)
{
	if (!*p)
		*list = *n;
	else
		(*p)->next = *n;
}

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
			modify_pointers(list, &prev, &next);
			append_token_list(&subhead, &subtail, current);
			current->next = NULL;
			current = prev;
		}
		append_pointers_values(list, &current, &prev);
	}
	return (subhead);
}
