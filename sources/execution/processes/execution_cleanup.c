/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 12:07:35 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	close_pipes(int (*pipefd)[2], int count)
{
	int	index;

	index = 0;
	while (index < count - 1)
	{
		close(pipefd[index][READ_END]);
		close(pipefd[index][WRITE_END]);
		index++;
	}
}

//
void	close_command_redirs(t_exec *node)
{
	if (node && node->redirs[INFILE] >= 0)
		close(node->redirs[INFILE]);
	if (node && node->redirs[OUTFILE] >= 0)
		close(node->redirs[OUTFILE]);
}

//
void	child_cleanup(t_shell **minishell, t_exec *node, int cmd)
{
	int	index;

	index = 0;
	close_command_redirs(node);
	free_execution_node((*minishell)->execution);
	free_tree((*minishell)->ast);
	while (index < cmd + 1)
	{
		close((*minishell)->pipefd[index][READ_END]);
		close((*minishell)->pipefd[index][WRITE_END]);
		index++;
	}
	free((*minishell)->pipefd);
	free((*minishell)->pids);
	close((*minishell)->original_stds[0]);
	close((*minishell)->original_stds[1]);
	free_minishell(*minishell);
}
