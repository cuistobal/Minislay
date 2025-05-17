/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/17 13:36:55 by chrleroy         ###   ########.fr       */
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

//Flag is triggered only if we're within a pipe
int	create_child_process(t_shell *minishell, t_exec **execution)
{
	int		status;
    int 	original_stds[2];

	if (!minishell || !*execution)
		return (GENERAL_ERROR);


	original_stds[0] = dup(STDIN_FILENO);
	original_stds[1] = dup(STDOUT_FILENO);

	handle_redirections(execution, original_stds);

    if (pipe((*execution)->pipe) != 0)
        return (GENERAL_ERROR);


	(*execution)->pid = fork();
	if ((*execution)->pid < 0)
		return (error_message(FORK_FAILED), GENERAL_ERROR);
	if ((*execution)->pid == 0)
	{
		if (handle_communication_in_child(execution) == GENERAL_ERROR)
			exit(GENERAL_ERROR);
		return (execute_command_in_child((*execution)->command, \
					(*execution)->environ));
	}
	else
		return (wait_module(*execution), restore_stds(original_stds), status);
}
