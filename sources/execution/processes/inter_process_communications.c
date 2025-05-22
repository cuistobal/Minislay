/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_process_communications.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/22 13:15:43 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
int	handle_communication_in_child(t_exec **node)
{
	if (dup2((*node)->pipe[0], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[1]);
	return (SUCCESS);
}

//
int	handle_communication_in_parent(t_exec **node)
{
	if (dup2((*node)->pipe[1], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[0]);
	return (SUCCESS);
}
*/

// This function redirects the STDIN/OUT streams acccording to the execution's
// node position.
int	pipe_communication(int pipefd[2], bool parent)
{
	int	new_fd;

	new_fd = dup2(STDIN_FILENO, pipefd[parent]);
	if (new_fd < 0)
		return (GENERAL_ERROR);
	return (new_fd);
}

//
int	handle_redirections(t_exec **execution, int original_stds[2])
{

    original_stds[0] = dup(STDIN_FILENO);
    if (original_stds[0] == -1)
		return (GENERAL_ERROR);
    original_stds[1] = dup(STDOUT_FILENO);
    if (original_stds[1] == -1)
		return (GENERAL_ERROR);

	//If we have a in redirection ->
/*
=======
>>>>>>> main:sources/execution/processes/ipc_module.c
	if ((*execution)->redirections[INFILE] != STDIN_FILENO)
	{
		if (dup2((*execution)->redirections[INFILE], STDIN_FILENO) != 0)
			return (GENERAL_ERROR);
		close((*execution)->redirections[INFILE]);
	}

	//If we have an out redirection ->

	if ((*execution)->redirections[OUTFILE] != STDOUT_FILENO)
	{
		if (dup2((*execution)->redirections[OUTFILE], STDOUT_FILENO) != 0)
			return (GENERAL_ERROR);
		close((*execution)->redirections[OUTFILE]);
	}
	return (SUCCESS);
*/
}
