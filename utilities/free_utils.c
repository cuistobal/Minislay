/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:47:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/07 08:58:13 by cuistobal        ###   ########.fr       */
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
	free(array);
	array = NULL;
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
	t_exec	*next;
	t_tokn	*current;

	next = NULL;
	while (execution)
	{
		current = execution->redirections;
		next = execution->next;
		if (execution->command)
			free_array(execution->command, 0);
		if (execution->environ)
			free_array(execution->environ, 0);
		while (current)
		{
            if (current->type != -1)
		    	close(current->type);
			if (current->value && strncmp(current->value, "<<", 2) == 0)
				unlink(current->value);
			free(current->value);
			move_pointer(&execution->redirections);			
			free(current);
			current = execution->redirections;
		}
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
	t_avlt	*branch;
	t_env	*current;

	index = 0;
	if (!minishell)
		return ;
	free_env_list(minishell->envp);
	free_env_list(minishell->local);
	free_env_list(minishell->command);
	free_env_list(minishell->special);
	free_avlt_tree(minishell->expt);
	free(minishell);
	minishell = NULL;
}
