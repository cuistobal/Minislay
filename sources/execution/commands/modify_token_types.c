/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_token_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:54:03 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/19 09:47:29 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"


// gros probleme avec ce fichier

//A retravailler
static void	append_redirections(t_tokn **head, t_tokn **tail, t_tokn **current)
{
	if (*head)
	{
		*tail = *current;
/*
		(*tail)->next = *current;
		move_pointer(tail);
*/
	}
	else
	{
		*head = *current;
		*tail = (*current)->next;
	}
	move_pointer(current);
	if (*current)
	{
		set_state(&(*current)->type, FILENAM);
		*tail = *current;
	//	move_pointer(current);
		if (*current)
			(*tail)->next = NULL;
	}
}

//
static void	append_token_type(t_tokn **expanded, t_tokn **current, t_tokn **previous, int *count)	
{
	*previous = *current;
	if (*current == *expanded)
		set_state(&(*expanded)->type, ARGUMNT);
	else
		set_state(&(*expanded)->type, COMMAND);
	(*count)++;
	move_pointer(current);
}

//
void	modify_token_types(t_tokn **expanded, t_tokn **redirections, int *count)
{
	t_tokn	*rtail;
	t_tokn	*rhead;
	t_tokn	*current;
	t_tokn	*previous;
	t_tokn	*redir_list;

	*count = 0;
	rtail = NULL;
	previous = NULL;
	current = *expanded;
	rhead = *redirections;
	while (current)
	{
		if (valid_lexeme(current, IRED, ARED))
		{
			append_redirections(&rhead, &rtail, &current);
			if (previous)
				previous->next = current;
			else
				*expanded = current;
		}
		else
			append_token_type(expanded, &current, &previous, count);
	}
}
