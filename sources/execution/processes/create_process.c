/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 09:19:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	create_child_process(t_shel	*minishell, char **command, char **env)
{
	int status;
	int	pipefd[2];

	if (pipe(pipefd) != 0)
		return error_message(PIPE_FAILED);
	pid_t pid = fork();
	if (pid == 0)
		execute_command(command, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("%d\n", WEXITSTATUS(status));
	}
}
