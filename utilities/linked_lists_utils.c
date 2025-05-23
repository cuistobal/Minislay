/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:43:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/23 16:05:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h" 


t_tokn	*get_tail_node(t_tokn **list)
{
	t_tokn	*current;

	current = *list;
	if (!current)
		return (NULL);
	printf("%s\n", current->value);
	while (current->next)
	{
		move_pointer(&current);

	printf("%s\n", current->value);
	}
	printf("%s\n", current->value);
	return (current);
}

void	append_exec_list(t_exec **head, t_exec **tail, t_exec *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
}

void	append_token_list(t_tokn **head, t_tokn **tail, t_tokn *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		if (*head && !*tail)
			*tail = get_tail_node(head);
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
}
