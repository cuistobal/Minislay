/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 18:02:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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
pid_t	create_and_execute_child(t_shell **minishell, t_exec *node, int pipefd[][2], int index)
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
		setup_redirections_in_child(minishell, node, pipefd, index);
		execute_command_in_child((node)->command, (node)->environ);
	}
	return (child);
}

//
static void	get_or_restore_stds(int fds[2], bool set)
{
	if (set)
	{
		fds[0] = dup(STDIN_FILENO);
		fds[1] = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
	}
}

//
void	redirections_in_parent(t_exec *node, int pipe[][2], int index)
{
	if (!node->next)
		return ;
	close(pipe[index][1]);
}

//
int	execute_commands(t_shell **minishell, t_exec *node)
{
	int				index;
	t_exec			*current;
	int				original_stds[2];
	pid_t			pids[BUFFER_SIZE];
	int				pipefd[BUFFER_SIZE][2];

	index = 0;
	current = node;
	get_or_restore_stds(original_stds, true);
	while (current)
	{
		if (current->next && pipe(pipefd[index]) < 0)
			return (GENERAL_ERROR);
		pids[index] = create_and_execute_child(minishell, current, pipefd, index);
		if (pids[index] < 0)
			return (GENERAL_ERROR);
		redirections_in_parent(current, pipefd, index);
		current = current->next;
		index++;
		if (index == BUFFER_SIZE)
			break ;
	}
	get_or_restore_stds(original_stds, false);
	if (index == BUFFER_SIZE)
			return (free_execution_node(node), GENERAL_ERROR);
	return (wait_module(pids, index));
}
