/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 13:50:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	execute_command_in_child(char **command, char **env)
{
	if (execve(*command, command, env) != 0)
	{
		free_array(command, 0);
		free_array(env, 0);
	}
	return (GENERAL_ERROR);
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
		return (wait_module(execution, flag));
	return (GENERAL_ERROR);
}
