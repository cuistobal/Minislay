/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 11:59:00 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	execute_command_in_child(char **command, char **envp)
{
	int	code;

	if (!command || !*command || !env || !*env)
		return (GENERAL_ERROR);
	else if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(envp, 0);
		exit(GENERAL_ERROR);
	}
	return (SUCCESS);
}

//
pid_t	create_and_execute_child(t_exec *node, int pipefd[][2], int index)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0)
	{
		//comportemment par defaut des signaux
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_redirections_in_child(node, pipefd, index);
		execute_command_in_child((node)->command, (node)->environ);
	}
	return (child);
}



static int	execute_binay(t_exec *current, pid_t pids[], int pipefd[][2], int index)
{
	pids[index] = create_and_execute_child(current, pipefd, index);
	if (pids[index] < 0)
		return (GENERAL_ERROR);
	redirections_in_parent(current, pipefd, index);
	return (SUCCESS);
}

//
int	execute_commands(t_shell **minishell, t_exec *node, int count)
{
	int				index;
	t_exec			*current;
	pid_t			pids[BUFFER_SIZE];
	int				pipefd[BUFFER_SIZE][2];

	index = 0;
	current = node;
	while (current && index < BUFFER_SIZE)
	{
		if (current->next && pipe(pipefd[index]) < 0)
			return (GENERAL_ERROR);
		if (is_builtin(*current->command))
			exec_builtin(current->command, current->environ, *minishell);
		else
			execute_binay(current, pids, pipefd, index);
		current = current->next;
		index++;
	}
	if (index == BUFFER_SIZE)
			return (wait_module(pids, index), execute_commands(minishell, current, count - index));
	return (wait_module(pids, index));
}
