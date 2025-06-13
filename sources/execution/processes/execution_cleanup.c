/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 13:20:08 by chrleroy         ###   ########.fr       */
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

/*
static void	cleanup_tree_in_child(t_tree **tree)
{
	if (!*tree)
		return ;
	cleanup_tree_in_child(&(*tree)->left);
	cleanup_tree_in_child(&(*tree)->right);
	free_tokens_adress(&(*tree)->tokens);
	*tree = NULL;
}
*/

//
void	child_cleanup(t_shell **minishell, t_exec *node, int cmd)
{
	int	index;

	index = 0;
	close_command_redirs(node);
	free_execution_node((*minishell)->execution);
	free_tree((*minishell)->ast);
	while (index < cmd)
	{
		close((*minishell)->pipefd[index][READ_END]);
		close((*minishell)->pipefd[index][WRITE_END]);
		index++;
	}
	free((*minishell)->pipefd);
	free((*minishell)->pids);
	//cleanup_tree_in_child(&(*minishell)->ast);
	close((*minishell)->original_stds[0]);
	close((*minishell)->original_stds[1]);
	free_minishell(*minishell);
}
