/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 13:09:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **envp)
{
	if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(command, 0);
		exit(GENERAL_ERROR);
	}
	return (SUCCESS);
}

//
static void	close_unused_pipes(t_exec **node, int pipefd[2])
{
	if (!(*node)->next)
		return ;
	close(pipefd[1]);
/*
	if ((*node)->redirections[INFILE] == STDIN_FILENO)
		(*node)->redirections[INFILE] = pipefd[0];
		*/
	if ((*node)->redirections[INFILE])	
		close(pipefd[0]);
}

//
pid_t	create_and_execute_child(t_shell **minishell, t_exec **node, int pipefd[][2], int index)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	else if (child == 0)
	{
		setup_redirections_in_child(minishell, node, pipefd, index);
		if (is_builtin(*(*node)->command))
			exec_builtin((*node)->command, (*node)->environ, *minishell);	
		execute_command_in_child((*node)->command, (*node)->environ);
	}
	return (child);
}

//
int	execute_commands(t_shell **minishell, t_exec *node, int *count)
{
	int		index;
	t_exec	*current;
	pid_t	pids[BUFFER_SIZE];
	int		pipefd[BUFFER_SIZE][2];

	if (*count >= BUFFER_SIZE)
		return printf("Malveillance max\n");
	index = 0;
	current = node;
	while (current)
	{
/*
		if (current->next)
		{
			if (pipe(pipefd[index]) < 0)
				return (GENERAL_ERROR);
		}
*/
		if (current->next && pipe(pipefd[index]) < 0)
			return (GENERAL_ERROR);
		if (!is_builtin(*current->command))
			pids[index] = create_and_execute_child(minishell, &current, pipefd, index);
		if (pids[index] < 0)
			return (GENERAL_ERROR);
		close_unused_pipes(&current, pipefd[index]);
		current = current->next;
		index++;
	}
	return (wait_module(pids, *count));
}
