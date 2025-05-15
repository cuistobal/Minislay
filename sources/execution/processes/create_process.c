/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 09:38:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **env)
{
	return (execve(*command, command + 1, env));
}

/*
bool	handle_communication_in_child(t_exec **node)
{
	if (dup2((*node)->pipe[0], STDIN_FILENO) != 0)
		return (false);
	close((*node)->pipe[1]);
}

//
bool	handle_communication_in_parent(t_exec **node)
{
	if (dup2((*node)->pipe[1], STDOUT_FILENO) != 0)
		return (false);

	close((*node)->pipe[0]);
}
*/

int	create_child_process(t_shel *minishell, t_exec *execution)
{
	char	*temp;
	int		status;
	int		pipefd[2];

	if (pipe(pipefd) != 0)
	{
		error_message(PIPE_FAILED);
		minishell->special[DEXTI] = ft_itoa(GENERAL_ERROR);
	}
	(execution)->pid = fork();
	if ((execution)->pid < 0)
		return (error_message(FORK_FAILED), -1);
	if ((execution)->pid == 0)
	{
	//	if (!handle_communication_in_child(execution))
	//		exit(REDIRECTION_ERROR);
		return (execute_command_in_child((execution)->command, (execution)->environ));
	}
	else
	{
		waitpid((execution)->pid, &status, 0);
		if (WIFEXITED(status))
		{
			//handle_communication_in_parent(execution);
		//	temp = minishell->special[DEXTI];
			minishell->special[DEXTI] = ft_itoa(WEXITSTATUS(status));
		//	dup2((*execution)->pipe[1], STDOUT_FILENO);
		//	free(temp);
			return (WEXITSTATUS(status));
		}
	}
	return (-1);
}
