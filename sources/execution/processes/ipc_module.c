/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 13:35:49 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	handle_communication_in_child(t_exec **node, bool flag)
{
	if (dup2((*node)->pipe[0], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[1]);
	return (SUCCESS);
}

//
int	handle_communication_in_parent(t_exec **node, bool flag)
{
	if (dup2((*node)->pipe[1], STDIN_FILENO) != 0)
		return (GENERAL_ERROR);
	close((*node)->pipe[0]);
	return (SUCCESS);
}

//
int	handle_redirections(t_exec *execution)
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
