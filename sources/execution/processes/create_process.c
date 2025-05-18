/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 09:10:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	execute_command_in_child(char **command, char **env)
{
	if (execve(*command, command, env) < 0)
	{
		free_array(command, 0);
		free_array(env, 0);
		exit(GENERAL_ERROR);
	}
	exit(SUCCESS);
}

//
static void restore_stds(int original_stds[2])
{
    dup2(original_stds[0], STDIN_FILENO);
    dup2(original_stds[1], STDOUT_FILENO);
}

//
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
//static int	close_unused_pipes(int fds[2][2], int cmd_index, int argc)
{
	if ((*node)->next)
	{
		close(pipefd[1]);
		close((*node)->redirections[INFILE]);
		(*node)->redirections[INFILE] = pipefd[0];
	}

}


/*
//Flag is triggered only if we're within a pipe
int	create_child_process(t_shell *minishell, t_exec **execution)
{
	pid_t	pid;
	int		status;
	int		pipefd[2];
    int 	original_stds[2];

	if (!minishell || !*execution)
		return (GENERAL_ERROR);

	if (pipe(pipefd) != 0)
		return (GENERAL_ERROR);

	original_stds[0] = STDIN_FILENO;
	original_stds[1] = STDOUT_FILENO;

//	handle_redirections(execution, original_stds);

	pid = fork();
	if (pid < 0)
		return (error_message(FORK_FAILED), GENERAL_ERROR);
	if (pid == 0)
	{
		setup_redirections_in_child(execution, pipefd);

//		if (handle_communication_in_child(execution) == GENERAL_ERROR)
//			exit(GENERAL_ERROR);
		return (execute_command_in_child((*execution)->command, \
					(*execution)->environ));
	}
	else
	{
		close_unused_pipes(execution, pipefd);
		return (wait_module(*execution), restore_stds(original_stds), status);
	}

	restore_stds(original_stds);
}
*/
