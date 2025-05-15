/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 13:17:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	execute_command_in_child(char **command, char **env)
{
	return (execve(*command, command + 1, env));
}

//
static int	handle_communication_in_child(t_exec **node, bool flag)
{
	if (dup2((*node)->pipe[0], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[1]);
	return (SUCCESS);
}

//
static int	handle_communication_in_parent(t_exec **node, bool flag)
{
	if (dup2((*node)->pipe[1], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[0]);
	return (SUCCESS);
}

//
static int	handle_redirections(t_exec *execution)
{
	if (execution->redirections[INFILE] != STDIN_FILENO)	
	{
		if (!dup2(execution->redirections[INFILE], STDIN_FILENO))
			return (GENERAL_ERROR);
	}
	if (execution->redirections[OUTFILE] != STDOUT_FILENO)	
	{
		if (!dup2(execution->redirections[OUTFILE], STDOUT_FILENO))
			return (GENERAL_ERROR);
	}
	return (SUCCESS);	
}

//Flag is triggered only if we're within a pipe
int	create_child_process(t_shel *minishell, t_exec *execution, bool flag)
{
	int		status;
	int		pipefd[2];

	if (pipe(pipefd) != 0)
		return (error_message(PIPE_FAILED), GENERAL_ERROR);
	handle_redirections(execution);
	execution->pid = fork();
	if ((execution)->pid < 0)
		return (error_message(FORK_FAILED), GENERAL_ERROR);
	if ((execution)->pid == 0)
	{
		if (handle_communication_in_child(&execution, flag) == GENERAL_ERROR)
			exit(GENERAL_ERROR);
		return (execute_command_in_child((execution)->command, (execution)->environ));
	}
	else
	{
		waitpid((execution)->pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (handle_communication_in_parent(&execution, flag) == GENERAL_ERROR)
				return (GENERAL_ERROR);
			return (WEXITSTATUS(status));
		}
	}
	return (GENERAL_ERROR);
}
