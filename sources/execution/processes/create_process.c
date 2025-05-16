/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 17:35:44 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	execute_command_in_child(char **command, char **env)
{
	if (execve(*command, command, env) != 0)
	{
		free_array(command, 0);
		free_array(env, 0);
		exit(GENERAL_ERROR);
	//	return(GENERAL_ERROR);
	}
	exit(SUCCESS);
//	return (SUCCESS);
}

//Flag is triggered only if we're within a pipe
int	create_child_process(t_shel *minishell, t_exec **execution)
{
	char	**cmd;
	char	**env;
	int		status;

	if (!minishell || !execution)
		return (GENERAL_ERROR);
	(*execution)->pid = fork();
	if ((*execution)->pid < 0)
		return (error_message(FORK_FAILED), GENERAL_ERROR);
	if ((*execution)->pid == 0)
	{
		env = (*execution)->environ;
		cmd = (*execution)->command;
		if (handle_communication_in_child(execution) == GENERAL_ERROR)
			exit(GENERAL_ERROR);
		return (execute_command_in_child(cmd, env));
	}
	else
	{
		status = wait_module(*execution);
		return (status);
	}
}
