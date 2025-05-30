/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:47:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 08:48:03 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	free_array(char **array, int count)
{
	int	index;

	index = 0;
	if (!*array)
		return ;
	if (count > 0)
	{
		while (count--)
		{
			free(array[count]);
			array[count] = NULL;
		}
	}
	else
	{
		while (array[index])
		{
			free(array[index]);
			array[index] = NULL;
			index++;
		}
	}
	free(*array);
	*array = NULL;
}

//
void	free_tree(t_tree *ast)
{
	if (!ast)
		return ;
	free_tree(ast->left);
	ast->left = NULL;
	free_tree(ast->right);
	ast->right = NULL;
	free(ast);
	ast = NULL;
}

//
void	free_execution_node(t_exec *execution)
{
/*
	int		index;
	t_exec	*next;

	if (!execution)
		return ;
	if ((execution)->environ)
		free_array((execution)->environ, 0);	
	if ((execution)->command)
		free_array((execution)->command, 0);
	next = (execution)->next;
	free(execution);
	execution = NULL;
	free_execution_node(next);
*/
	t_exec	*next;

	next = NULL;
	while (execution)
	{
		next = execution->next;
		if (execution->command)
			free_array(execution->command, 0);
		if (execution->environ)
			free_array(execution->environ, 0);
		free(execution);
		execution = next;
	}
}

//
void	free_minishell(t_shell *minishell)
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
		if (current->var[KEY])
			free(current->var[KEY]);
		if (current->var[VALUE])
			free(current->var[VALUE]);
		free(current);
		current = (minishell)->envp;
	}
	branch = (minishell)->expt;
	if (branch)
		free_avlt_tree(branch);
	while (index < DKCT)
	{
        if (minishell->special[index])
	    	free((minishell)->special[index]);
		index++;
	}
	while (minishell->local)
	{
		current = minishell->local;
		minishell->local = minishell->local->next;
		free(current);
	}
	while (minishell->command)
	{
		current = minishell->command;
		minishell->command = minishell->command->next;
		free(current);
	}
}
