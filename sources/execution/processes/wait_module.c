/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 13:55:43 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	wait_module(t_exec *execution, bool flag)
{
	int	status;

	waitpid((execution)->pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (handle_communication_in_parent(&execution, flag) == GENERAL_ERROR)
			return (GENERAL_ERROR);
		return (WEXITSTATUS(status));
	}
//	return (GENERAL_ERROR);
}
