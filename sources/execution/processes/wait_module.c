/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 18:22:43 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	return_exit_code(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}

static int get_exit_code_from_minishell(t_shell *minishell, int ret)
{
	int		ccode;
	t_env	*code;

	if (ret != EXIT_CODE)
		return (ret);
	code = find_special_env_variable(minishell, LAST_CMD_ECODE);
	if (!code || (!code->var[KEY] || !*code->var[KEY]))
		ccode = GENERAL_ERROR;
	else
		ccode = atoi(code->var[KEY]);
	return (ccode);
}

//
int	wait_module(t_shell *minishell, pid_t *pids, int count, int ret)
{
	bool	error;
	int		index;
	int		status;

	index = 0;
	while (count < index)
	{
		status = return_exit_code(pids[index]);
		if (status != EXIT_CODE)
			append_exit_code(minishell, status, true);
		count++;
	}
	return (ret);
}
