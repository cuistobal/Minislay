/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:15:42 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 16:48:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	modify_token_list(t_tokn **head, t_tokn **tail, t_tokn *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new->next;
	}
	else
	{
		(*tail)->next = new;
		move_pointer(tail);
		move_pointer(tail);
	}
}
//
static void	assign_redirections(t_tokn *redirections, t_tokn **infile, t_tokn **outfile)
{
	t_tokn	*temp;
	t_tokn	*otail;
	t_tokn	*itail;

	itail = NULL;
	otail = NULL;
	while (redirections)
	{
		temp = redirections;
		if (*redirections->value == '<')
			modify_token_list(infile, &itail, temp);
		else
			modify_token_list(outfile, &otail, temp);
		move_pointer(&redirections);
		move_pointer(&redirections);
	}
	if (itail)
		itail->next = NULL;
	if (otail)
		otail->next = NULL;
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
static char	**rebuild_env(t_shell *minishell)
{
	int		size;
	int		index;
	char	**env;
	char	*temp[2];
	t_env	*current;

	index = 0;
	size = 50;
	current = minishell->envp;
	env = (char **)malloc(sizeof(char *) * size);
	if (!env)
		return (NULL);
	reset_array(env, 0, size);
	while (current)
	{
		reset_array(temp, 0, 2);
		if (index == size - 1)
			env = (char **)resize_array(env, sizeof(char *), &size);
		if (!env)
			return (NULL);
		temp[0] = current->var[0];
		temp[1] = current->var[1];
		if (!join_env(&env[index++], temp))
			return (free_array(env, size), NULL);
		current = current->next;
	}
	return (env);
}

//
t_exec	*create_execution_node(t_shell **minishell, t_tree *ast)
{
	t_exec	*node;
	t_tokn	*arguments;
	t_tokn	*redirections;

	node = NULL;
	arguments = NULL;
	redirections = NULL;
	if (!minishell || !ast)
		return (NULL);
	node = malloc(sizeof(t_exec));
	//	prepare_for_exec(minishell, ast, &redirections);
	if (!node)
		return (set_error_code(minishell, GENERAL_ERROR), NULL);
	node->command = get_command_and_arguments(*minishell, arguments);
	if (!node->command)
		return (free_execution_node(node), set_error_code(minishell, GENERAL_ERROR), NULL);
	node->environ = rebuild_env(*minishell);
	if (!node->environ)
		return (set_error_code(minishell, GENERAL_ERROR), NULL);
	node->redirections[HERE_DOC] = redirections;
	node->redirections[INFILE] = NULL;
	node->redirections[OUTFILE] = NULL;
	node->next = NULL;
	return (node);
}
