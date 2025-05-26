/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:16:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/26 11:12:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	append_heredoc_queue(t_tokn **head, t_tokn **tail, t_tokn *new)
{
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		*tail = new->next;
	}
	else
	{
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
}

/*
static bool	redirections_queue(t_shell *minishell, t_tokn **list, t_tokn **heredocs, int redir[])
{
	t_tokn	*tail;
	t_tokn	*prev;
	t_tokn	*current;

	tail = NULL;
	current = *list;
	while (current)
	{
		prev = current;
		move_pointer(&current);
		if (!current)
			return (printf("ERROR\n"), false);
		if (is_state_active(prev->type, HDOC))
			append_heredoc_queue(heredocs, &tail, current);

//Open the file, we'll close it if its not the last one of its family 

		else if (is_state_active(prev->type, IRED))
	//		open()
		else if (is_state_active(prev->type, ORED))
	//		.
		else if (is_state_active(prev->type, ARED))
	//		.
		move_pointer(&current);
	}
	if (tail)
		tail->next = NULL;
}
*/
//
int	setup_redirections_in_child(t_shell **minishell, t_exec **node, int pipe[][2], int cmd)
{	
	if (cmd > 0)
	{
		dup2(pipe[cmd - 1][0], STDIN_FILENO);
		close(pipe[cmd - 1][1]);
	}
	else if ((*node)->next)
	{
		dup2(pipe[cmd][1], STDOUT_FILENO);
        close(pipe[cmd][0]);
	}
	return (SUCCESS);
}
