/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 22:01:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// This function sets up the redirections in the child process.
// It handles input and output redirections based on the node's redirs array.
int	execute_command_in_child(t_shell **minishell, t_exec *node, int cmd)
{
	if (node->redirs[INFILE] < -1 || node->redirs[OUTFILE] < -1)
	{
		child_cleanup(minishell, node, cmd);
		exit(GENERAL_ERROR);
	}
	if (!node->command || !*node->command)
	{
		child_cleanup(minishell, node, cmd);
		exit(COMMAND_NOT_FOUND);
	}
	if (execve(*node->command, node->command, node->environ) < 0)
	{
		child_cleanup(minishell, node, cmd);
		exit(COMMAND_NOT_FOUND);
	}
	return (SUCCESS);
}

//Creates a child process to execute the command.
//It sets up the necessary redirections and executes the command in the child 
//process.
//If the fork fails, it returns -1.
//If the child process is created successfully, it sets up the signal handlers 
//to default,
//sets up the redirections in the child process, and executes the command using 
//execve.
//The function returns the child's PID on success, or -1 on failure.
// It is used to create a new process for executing commands in the shell.
// The child process will handle the command execution, while the parent process
// will manage
// the redirections and wait for the child to finish.
// It is a crucial part of the shell's execution model, allowing for concurrent 
// command execution.
// It is used to create a new process for executing commands in the shell.
pid_t	create_and_execute_child(t_shell **minishell, t_exec *node, \
		int pipefd[][2], int index)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections_in_child(*minishell, node, \
					pipefd, index) == SUCCESS)
		{
			execute_command_in_child(minishell, node, index);
			exit(COMMAND_EXEC);
		}
		child_cleanup(minishell, node, index);
		exit(GENERAL_ERROR);
	}
	return (child);
}

//
static pid_t	execute_binay(t_shell **minishell, t_exec *current, \
		int pipefd[][2], int index)
{
	pid_t	pid;

	pid = create_and_execute_child(minishell, current, pipefd, index);
	if (pid < 0)
		return (GENERAL_ERROR);
	redirections_in_parent(current, pipefd, index);
	return (pid);
}

static int	execute_commands_helper(t_shell **m, int *ret, int count)
{
	if (count <= 0)
		return (*ret = SUCCESS, SUCCESS);
	(*m)->pids = malloc(sizeof(pid_t) * count);
	(*m)->pipefd = malloc(sizeof(int *) * 2 * (count - 1));
	if (!(*m)->pids || !(*m)->pipefd)
		return (free((*m)->pids), free((*m)->pipefd), *ret = GENERAL_ERROR, \
				GENERAL_ERROR);
	*ret = -1;
	return (*ret = -1, SUCCESS);
}

//
int	execute_commands(t_shell **m, t_exec *node, int count)
{
	int		ret;
	int		index;

	index = 0;
	if (execute_commands_helper(m, &ret, count) == ret)
		return (ret);
	while (node && index < count)
	{
		if (node->next && pipe((*m)->pipefd[index]) < 0)
			return (free((*m)->pids), close_pipes((*m)->pipefd, index), \
					free((*m)->pipefd), GENERAL_ERROR);
		if (node->command && is_builtin(*node->command) && (node->next || \
					index != 0))
			(*m)->pids[index] = execute_builtin(node, (*m)->pipefd, \
						index, m);
		else if (node->command && is_builtin(*node->command))
			ret = execute_simple_builtin(node, m);
		else
			(*m)->pids[index] = execute_binay(m, node, (*m)->pipefd, index);
		close_command_redirs(node);
		node = node->next;
		index++;
	}
	return (close_pipes((*m)->pipefd, count), free((*m)->pipefd), \
			wait_module((*m), (*m)->pids, index, ret));
}
