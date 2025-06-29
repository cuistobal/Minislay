/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_module.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 22:25:49 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	get_last_exit_code(t_shell *minishell)
{
	t_env	*code;

	code = find_special_env_variable(minishell, 3);
	if (!code || !code->var[VALUE] || !*code->var[VALUE])
		return (GENERAL_ERROR);
	return ((int)ft_atol(code->var[VALUE]));
}

static void	wait_module_helper(t_shell *minishell, int *last_code, int status)
{
	if (WIFEXITED(status))
	{
		*last_code = WEXITSTATUS(status);
		append_exit_code(minishell, *last_code);
	}
	else if (WIFSIGNALED(status))
	{
		*last_code = 128 + WTERMSIG(status);
		append_exit_code(minishell, *last_code);
	}
}

//
int	wait_module(t_shell *minishell, pid_t *pids, int count, int ret)
{
	int		index;
	int		status;
	int		last_code;

	index = 0;
	last_code = 0;
	if (ret > -1)
		return (free(minishell->pids), minishell->pids = NULL, ret);
	while (index < count)
	{
		if (waitpid(pids[index], &status, 0) == -1)
			return (get_last_exit_code(minishell));
		wait_module_helper(minishell, &last_code, status);
		index++;
	}
	return (free(minishell->pids), minishell->pids = NULL, last_code);
}
