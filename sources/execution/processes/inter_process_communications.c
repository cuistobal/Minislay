/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_process_communications.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 20:01:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	my_dup(int source)
{
	int	newfd;

	newfd = dup(source);
	if (newfd < 0)
		error_message(DUP_FAILED);
	return (newfd);
}

//
int	my_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret < 0)
		return (error_message(DUP_FAILED), GENERAL_ERROR);
	return (SUCCESS);
}

//
void	get_or_restore_stds(int fds[2], bool set)
{
	static struct termios	original;
	struct termios			term;

	if (set)
	{
		if (isatty(STDIN_FILENO))
			tcgetattr(STDIN_FILENO, &original);
		fds[0] = STDIN_FILENO;
		fds[1] = STDOUT_FILENO;
	}
	else
	{
		if (isatty(STDIN_FILENO))
		{
			tcgetattr(STDIN_FILENO, &term);
			term = original;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
	}
}

//
int	stdin_management(t_exec *node, int pipefd[][2], int index)
{
	int	old;
	int	infile;

	infile = node->redirs[INFILE];
	if (infile < -1)
		return (GENERAL_ERROR);
	else if (infile >= 0)
	{
		if (my_dup2(infile, STDIN_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(infile);
	}
	else if (index > 0)
	{
		old = pipefd[index - 1][READ_END];
		if (my_dup2(pipefd[index - 1][READ_END], STDIN_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(old);
	}
	return (SUCCESS);
}

//
int	stdout_management(t_exec *node, int pipefd[][2], int index)
{
	int	old;
	int	outfile;

	outfile = node->redirs[OUTFILE];
	if (outfile < -1)
		return (GENERAL_ERROR);
	if (outfile >= 0)
	{
		if (my_dup2(outfile, STDOUT_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(outfile);
	}
	else if (node->next)
	{
		old = pipefd[index][WRITE_END];
		if (my_dup2(pipefd[index][WRITE_END], STDOUT_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(old);
	}
	return (SUCCESS);
}
