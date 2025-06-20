/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:50:21 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 22:18:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	execute_simple_builtin(t_exec *current,	t_shell **minishell)
{
	int		fd;
	int		ret;
	char	*tty_path;

	if (current->redirs[INFILE] < -1 || current->redirs[OUTFILE] < -1)
		return (GENERAL_ERROR);
	tty_path = NULL;
	if (isatty(STDIN_FILENO))
		tty_path = ttyname(STDIN_FILENO);
	if (current->redirs[INFILE] != -1)
		dup2(current->redirs[INFILE], STDIN_FILENO);
	if (current->redirs[OUTFILE] != -1)
		dup2(current->redirs[OUTFILE], STDOUT_FILENO);
	ret = exec_builtin(current->command, minishell);
	if (tty_path && (current->redirs[INFILE] != -1 || \
				current->redirs[OUTFILE] != -1))
	{
		fd = open(tty_path, O_RDWR);
		if (fd < 0)
			return (GENERAL_ERROR);
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (ret);
}

//
pid_t	execute_builtin(t_exec *current, int pipefd[][2], int index, \
		t_shell **minishell)
{
	int		ret;
	pid_t	pid;

	ret = GENERAL_ERROR;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections_in_child(*minishell, current, pipefd, \
					index) == SUCCESS)
			ret = exec_builtin(current->command, minishell);
		child_cleanup(minishell, current, index);
		exit(ret);
	}
	return (redirections_in_parent(current, pipefd, index), pid);
}
