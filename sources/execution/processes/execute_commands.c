/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/25 16:07:20 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **envp)
{
	int	code;

	if (!command || !*command || !env || !*env)
		return (GENERAL_ERROR);
	if (is_builtin(*command))
	{
		code = exec_builtin(command, envp, NULL);
		free_array(command, 0);	
		free_array(envp, 0);	
		exit(code);
	}
	else if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(envp, 0);
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
//	if ((*node)->redirections[INFILE])	
//		close(pipefd[0]);
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
		//comportemment par defaut des signaux
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_redirections_in_child(minishell, node, pipefd, index);
		execute_command_in_child((*node)->command, (*node)->environ);
	}
	return (child);
}

//
int	execute_commands(t_shell **minishell, t_exec *node)
{
	int		index;
	t_exec	*current;
	pid_t	pids[BUFFER_SIZE];
	int		pipefd[BUFFER_SIZE][2];

	index = 0;
	current = node;
	while (current)
	{
		if (current->next && pipe(pipefd[index]) < 0)
			return (GENERAL_ERROR);
		pids[index] = create_and_execute_child(minishell, &current, pipefd, index);
		if (pids[index] < 0)
			return (GENERAL_ERROR);
		close_unused_pipes(&current, pipefd[index]);
		current = current->next;
		index++;
		if (index == BUFFER_SIZE)
			break ;
	}
	if (index == BUFFER_SIZE)
			return (free_execution_node(node), GENERAL_ERROR);
	return (wait_module(pids, index));
}
