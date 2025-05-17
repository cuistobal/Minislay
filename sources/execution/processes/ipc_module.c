/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 18:14:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
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

//
int	handle_redirections(t_exec **execution, int original_stds[2])
{
    original_stds[0] = dup(STDIN_FILENO);
    if (original_stds[0] == -1)
		return (GENERAL_ERROR);
    original_stds[1] = dup(STDOUT_FILENO);
    if (original_stds[1] == -1)
		return (GENERAL_ERROR);
	if ((*execution)->redirections[INFILE] != STDIN_FILENO)
	{
		if (dup2((*execution)->redirections[INFILE], STDIN_FILENO) != 0)
			return (GENERAL_ERROR);
	}
	if ((*execution)->redirections[OUTFILE] != STDOUT_FILENO)
	{
		if (dup2((*execution)->redirections[OUTFILE], STDOUT_FILENO) != 0)
			return (GENERAL_ERROR);
	}
	return (SUCCESS);
}
