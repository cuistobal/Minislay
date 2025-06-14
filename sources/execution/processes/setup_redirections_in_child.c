/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:00:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 19:52:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	close_unused_pipes(t_exec *node, int pipefd[][2], int index)
{
	if (index > 0)
	{
		close(pipefd[index - 1][READ_END]);
		close(pipefd[index - 1][WRITE_END]);
	}	
	if (node->next)
	{
		close(pipefd[index][READ_END]);
		close(pipefd[index][WRITE_END]);
	}
	return (SUCCESS);
}

//
static void	close_unused_redirs(t_shell *minishell, int cmd)
{
	int		index;
	t_exec	*nodes;

	index = 0;
	nodes = minishell->execution;
	while (nodes)
	{
		if (index != cmd && nodes->redirs[INFILE] >= 0)
			close(nodes->redirs[INFILE]);
		if (index != cmd && nodes->redirs[OUTFILE] >= 0)
			close(nodes->redirs[OUTFILE]);
		nodes = nodes->next;
		index++;
	}
}

static int	close_pipes_r_fail(t_exec *node, int pipefd[][2], int index, \
		int ret)
{
	if (!node->next)
		return (ret);
	close(pipefd[index][0]);
	close(pipefd[index][1]);
	return (ret);
}

//
int	setup_redirections_in_child(t_shell *minishell, t_exec *node, \
		int pipefd[][2], int index)
{
	int	ret;

	ret = stdin_management(node, pipefd, index);
	if (ret != SUCCESS)
		return (close_pipes_r_fail(node, pipefd, index, ret));
	ret = stdout_management(node, pipefd, index);
	if (ret != SUCCESS)
		return (close_pipes_r_fail(node, pipefd, index, ret));
	ret = close_unused_pipes(node, pipefd, index);
	if (ret != SUCCESS)
		return (close_pipes_r_fail(node, pipefd, index, ret));
	close_unused_redirs(minishell, index);
	return (SUCCESS);
}
