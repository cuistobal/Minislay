/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipelines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/17 20:04:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//This function handles redirections

static int	setup_redirections_in_child(t_exec **node, int pipefd[2])
{
	//if there is an input redirection
	if ((*node)->redirections[INFILE] != STDIN_FILENO)
	{
		if (dup2((*node)->redirections[INFILE], STDIN_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close((*node)->redirections[INFILE]);
	}

	//if there is an out redirection
	if ((*node)->redirections[OUTFILE] != STDOUT_FILENO)
	{
		if (dup2((*node)->redirections[OUTFILE], STDOUT_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close((*node)->redirections[OUTFILE]);
	}
	else if ((*node)->next)
	{
		//redirect command in pipe
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			return (REDIRECTION_ERROR);
		close(pipefd[1]);
	}
	close(pipefd[0]);
	return (SUCCESS);
}

//
static void	close_unused_pipes(t_exec **node, int pipefd[2])
{
	if (!(*node)->next)
		return ;
	close(pipefd[1]);
	if ((*node)->redirections[INFILE] == STDIN_FILENO)
		(*node)->redirections[INFILE] = pipefd[0];
}

//
pid_t	create_and_execute_child(t_exec **node, int pipefd[2])
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	else if (child == 0)
	{
		setup_redirections_in_child(node, pipefd);
		execute_command_in_child((*node)->command, (*node)->environ);
	}
	return (child);
}

//
int	execute_pipelines(t_shell **minishell, t_exec *node)
{
	t_exec	*current;
	int		pipefd[2];

	current = node;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd) < 0)
				return (GENERAL_ERROR);
		}
		current->pid = create_and_execute_child(&current, pipefd);
		if (node->pid < 0)
			return (GENERAL_ERROR);
		close_unused_pipes(&current, pipefd);
		current = current->next;
	}
	return (wait_module(node));
}
