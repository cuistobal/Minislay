/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:22:28 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 10:10:58 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
void	do_pipe(t_shel **minishell, t_tree *ast, t_exec **node)
{
	t_exec *head;

	head = *node;
	if (is_state_active(ast->left->tokens->type, PIPE))
//		traverse_ast(minishell, ast->left, &(*node)->next);
	{
		if (*node)
			do_pipe(minishell, ast->left, &(*node)->next);
		else
			do_pipe(minishell, ast->left, node);
	}
	else
	{
		if (!*node)
			*node = create_execution_node(minishell, ast->left);
		else
			(*node)->next = create_execution_node(minishell, ast->left);
	}
	if (is_state_active(ast->right->tokens->type, PIPE))
//		traverse_ast(minishell, ast->right, &(*node)->next);
		do_pipe(minishell, ast->left, &(*node)->next);
	else
	{
		if (!*node)
			*node = create_execution_node(minishell, ast->right);
		else
			(*node)->next = create_execution_node(minishell, ast->right);
	}
//	execute_pipe(node);
}
*/
t_exec	*do_pipe(t_shel **minishell, t_tree *ast)
{
	t_exec	*pipeline;

	pipeline = NULL;
	if (ast->left)
	{
		if (is_state_active(ast->left->tokens->type, PIPE))
			pipeline = do_pipe(minishell, ast->left);
		else if (is_state_active(ast->left->tokens->type, LAND | LORR))
			traverse_ast(minishell, ast->left);
		else
			pipeline = create_execution_node(minishell, ast);
	}
	if (ast->right)
	{
		if (is_state_active(ast->right->tokens->type, PIPE))
			pipeline = do_pipe(minishell, ast->right);
		else if (is_state_active(ast->right->tokens->type, LAND | LORR))
			traverse_ast(minishell, ast->right);
		else
	}
	
}
/*
void	do_and(t_shel **minishell, t_tree *ast)
{
	
}

//
void	do_or(t_shel **minishell, t_tree *ast)
{
	
}
*/
