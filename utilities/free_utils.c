/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:47:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 18:53:08 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	free_tree(t_tree *ast)
{
	t_tokn	*current;

	current = NULL;
	if (!ast)
		return ;
	free_tree(ast->left);
	ast->left = NULL;
	free_tree(ast->right);
	ast->right = NULL;
	free(ast);
	ast = NULL;
}

static void	free_redirections(t_tokn **current)
{
	t_tokn	*prev;

	while (*current)
	{
		prev = *current;
		if ((*current)->type >= 0)
			close((*current)->type);
		else if ((*current)->value && ft_strncmp((*current)->value, \
					HEREDOC_PREFIX, ft_strlen(HEREDOC_PREFIX)) == 0)
			unlink((*current)->value);
		move_pointer(current);
		free(prev->value);
		prev->value = NULL;
		free(prev);
		prev = *current;
	}
}

void	free_execution_node(t_exec *execution)
{
	t_exec	*next;

	while (execution)
	{
		next = execution->next;
		if (execution->command)
			free_array(execution->command, 0);
		if (execution->environ)
			free_array(execution->environ, 0);
		if (execution->redirections)
			free_redirections(&execution->redirections);
		free_tokens(execution->assignations);
		free(execution);
		execution = next;
	}
}

//
void	free_env_list(t_env *list)
{
	t_env	*current;

	current = list;
	while (current)
	{
		list = list->next;
		if (current->var[KEY])
			free(current->var[KEY]);
		if (current->var[VALUE])
			free(current->var[VALUE]);
		free(current);
		current = list;
	}
}

//
void	free_minishell(t_shell *minishell)
{
	int		index;

	index = 0;
	if (!minishell)
		return ;
	free_env_list(minishell->envp);
	free_env_list(minishell->local);
	free_env_list(minishell->command);
	free_env_list(minishell->special);
	free(minishell);
	minishell = NULL;
}
