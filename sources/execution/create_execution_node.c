/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:15:42 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 16:27:22 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	assign_redirections(t_exec **node, t_tokn *redirections)
{
	t_tokn	*input;
	t_tokn	*output;

	input = NULL;
	output = NULL;
	while (redirections)
	{	
		if (*redirections->value == '<')
			input = redirections;
		else
			output = redirections;
		move_pointer(&redirections);
	}
	if (input)
		(*node)->redirections[CMD_INPUT] = input->type;
	else
		(*node)->redirections[CMD_INPUT] = STDIN_FILENO;
	if (output)
		(*node)->redirections[CMD_OUTPUT] = output->type;
	else
		(*node)->redirections[CMD_OUTPUT] = STDOUT_FILENO;
}

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
	t_exec	*node;
	t_tokn	*redirections;

	node = NULL;
	redirections = NULL;
	if (!minishell || !ast)
		return (NULL);
	node = prepare_for_exec(minishell, ast, &redirections);
	if (!node)
		return (set_error_code(minishell, GENERAL_ERROR), NULL);
	esize = 1;
	node->environ = rebuild_env(*minishell, &esize);
	if (!node->environ)
		return (set_error_code(minishell, GENERAL_ERROR), NULL);
	node->pid = -1;
/*
	if (pipe(node->pipe) != 0)
		return (free_execution_node(node), NULL);
*/
	assign_redirections(&node, redirections);
	return (node);
}
