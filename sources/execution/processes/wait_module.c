/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 08:40:28 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int wait_module(t_shell *minishell, pid_t *pids, int count)
{
    bool    error;
    int     index;
    int     status;
	int		last_code;

    index = 0;
	last_code = 0;
    while (index < count)
    {
		waitpid(pids[index], &status, WEXITED);
		if (WIFEXITED(status))
		{
			last_code = WEXITSTATUS(status);
			append_exit_code(minishell, last_code);
		}
		else if (WIFSIGNALED(status))
		{
			last_code = 128 + WTERMSIG(status);
			append_exit_code(minishell, last_code);
		}
        index++;
    }
    return (last_code);
}
