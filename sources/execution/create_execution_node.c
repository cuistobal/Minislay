/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:15:42 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 09:27:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	join_env(char **joined, char *temp[2])
{
	char	*merged;

	merged = ft_strjoin(strdup(temp[0]), strdup("\""));
	if (!merged)
		return (free(merged), merged = NULL, false);
	merged = ft_strjoin(merged, strdup(temp[1]));
	if (!merged)
		return (free(merged), merged = NULL,false);
	return (*joined = merged, true);
}

// Had to declare a current pointer bc the original minishel pointer is moved
// for some reason.
static char	**rebuild_env(t_shel *minishell, int *size)
{
	int		index;
	char	**env;
	char	*temp[2];
	t_env	*current;

	index = 0;
	current = minishell->envp;
	env = (char **)malloc(sizeof(char *) * *size);
	if (!env)
		return (NULL);
	reset_array(env, 0, *size);
	while (current)
	{
		reset_array(temp, 0, 2);
		if (index == *size - 1)
			env = (char **)resize_array(env, sizeof(char *), size);
		if (!env)
			return (NULL);
		temp[0] = current->var[0];
		temp[1] = current->var[1];
		if (!join_env(&env[index++], temp))
			return (free_array(env, *size), NULL);
		current = current->next;
	}
	return (env);
}

//
t_exec	*create_execution_node(t_shel **minishell, t_tree *ast)
{
	int		esize;
	int		csize;
	char	**env;
	char	**command;
	t_exec	*new_node;

	if (!minishell || !ast)
		return (NULL);
	
	new_node = (t_exec *)malloc(sizeof(t_exec));
	if (!new_node)
		return (NULL);

	csize = 1;
	new_node->command = prepare_for_exec(minishell, ast, &csize);
	if (!command)
		return (error_message(INV_COMMAND), NULL);
	esize = 1;
	new_node->env = rebuild_env(*minishell, &esize);
	if (!env)
		return (free_array(env, esize), error_message(INV_ENV), NULL);
	new_node->pid = -1;
	pipe(new_node->pipe);
	return (new_node);
}
