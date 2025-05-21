/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 14:08:10 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	return_exit_code(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}


int	wait_module(pid_t *pids, int count)
{
	int	index;
	int	status;
	
	index = 0;
	while (count < index)
	{
		status = return_exit_code(pids[index]);
		if (status != 0)
			printf("Error exec\n");
		count++;
	}
	return (GENERAL_ERROR);
}
