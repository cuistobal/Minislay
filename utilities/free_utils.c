/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:47:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 13:59:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	free_array(char **array, int count)
{
	if (array)
	{
		while (count--)
		{
			free(array[count]);
			array[count] = NULL;
		}
		free(array);
		array = NULL;
	}
}

//
void	free_tree(t_tree *ast)
{
	if (ast)
	{
		free_tree(ast->left);
		free_tree(ast->right);
		free_tokens(ast->tokens);	
	}
}

void	free_execution_node(t_exec *execution)
{
	int	index;

	if (!execution)
		return ;
	if ((execution)->environ)
	{
		index = 0;
		while ((execution)->environ[index])
		{
			free((execution)->environ[index]);
			index++;
		}
		free((execution)->environ);
	}
	if ((execution)->command)
	{
		index = 0;
		while ((execution)->command[index])
		{
			free((execution)->command[index]);
			index++;
		}
		free((execution)->command);
	}
	free(execution);
	execution = NULL;
}

//
void	free_minishell(t_shel *minishell)
{
	int		index;
	t_avlt	*branch;
	t_env	*current;

	index = 0;
	if (!minishell)
		return ;
	current = (minishell)->envp;
	while (current)
	{
		(minishell)->envp = (minishell)->envp->next;
		free(current);
		current = (minishell)->envp;
	}
	branch = (minishell)->expt;
	if (branch)
		free_avlt_tree(branch);
/*
	while ((*minishell)->special[index])
	{
		free((*minishell)->special[index]);
		index++;
	}
*/
//	free((*minishell)->special[index]);
	free((minishell)->special);
}
