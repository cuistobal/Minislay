/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/17 18:57:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int  execute_branch(t_shell *minishell, t_exec **node)
{
	int	pipefd[2];

	if (is_builtin(*(*node)->command))
		return (exec_builtin((*node)->command, (*node)->environ, minishell));
	return (create_child_process(minishell, node));
}

//
t_exec	*handle_operators(t_shell **minishell, t_tree *ast)
{
	t_exec	*node;

	node = NULL;
/*
	if (is_state_active(ast->tokens->type, LAND))	
		node = do_and();
	else if (is_state_active(ast->tokens->type, LORR))	
		node =do_or();
*/
	return (node);
}

//
static bool	is_pipeline(t_tokn *list)
{
	while (list)
	{
		if (is_state_active(list->type, PIPE))
			return (true);
		else
			list = list->next;
	}
	return (false);
}

//
void	execute_pipeline(t_shell **minishell, t_exec *execution)
{
	t_exec	*current;
	int		original_stds[2];

	current = execution;
	
	//Keep track of the current STDS

	original_stds[0] = dup(STDIN_FILENO);
	original_stds[1] = dup(STDOUT_FILENO);

	//Create all child processes
	while (current)
	{
		execute_branch(*minishell, &current);
		if (!current->next)
		{
/*
			dup2(original_stds[0], STDIN_FILENO);
			dup2(original_stds[1], STDOUT_FILENO);	
*/
		}
		current = current->next;
	}

	//Wait for each of them to finish

	wait_module(execution);
}


//
void	traverse_ast(t_shell **minishell, t_tree *ast)
{
	t_exec      *node;

	node = NULL;
	if (!ast)
		return ;
	else if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else if (is_pipeline(ast->tokens))
	{
		node = handle_pipeline(minishell, ast);
		execute_pipeline(minishell, node);
		free_execution_node(node);
	}
	else
	{
		node = create_execution_node(minishell, ast);
		execute_branch(*minishell, &node);
		free_execution_node(node);
	}
	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);
}
