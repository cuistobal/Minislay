/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_token_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:54:03 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 09:36:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	redir_list(t_tokn **red, t_tokn *prev, t_tokn **rtail, t_tokn *cur)
{
	if (valid_lexeme(cur, IRED, ARED) || valid_lexeme(prev, IRED, ARED))
	{
		if (!valid_lexeme(cur, IRED, ARED))
			set_state(&cur->type, FILENAM);
		if (*red && !rtail)
			*rtail = get_tail_node(red);
		append_token_list(red, rtail, cur);
	}
	return (false);
}

//
static void	command_list(t_tokn **chead, t_tokn **ctail, t_tokn *current)
{
	if (*chead)
		set_state(&current->type, ARGUMNT);
	else
		set_state(&current->type, COMMAND);
	append_token_list(chead, ctail, current);
}

//
void	modify_token_types(t_tokn **expanded, t_tokn **redirections)
{
	t_tokn	*prev;
	t_tokn	*rtail;
	t_tokn	*ctail;
	t_tokn	*chead;
	t_tokn	*current;

	prev = NULL;
	rtail = NULL;
	ctail = NULL;
	chead = NULL;
	current = *expanded;
	while (current)
	{
		if (!redir_list(redirections, prev, &rtail, current))
			command_list(&chead, &ctail, current);
		prev = current;
		current = current->next;
	}
	*expanded = chead;
	if (ctail)
		ctail->next = NULL;
	if (rtail)
		rtail->next = NULL;
}
