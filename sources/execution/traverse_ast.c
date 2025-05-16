/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 11:20:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int  execute_branch(t_shel *minishell, t_exec *node, int ctype)
{
    int	exit_code;

    exit_code = -1;
	if (is_builtin(*node->command) && !(ctype & PIPE))
		return (exec_builtin(minishell, node));
	else
		exit_code = create_child_process(minishell, node, ctype & PIPE);
    return (exit_code);
}

//
t_exec	*do_pipe(t_shel **minishell, t_tree *ast)
{
	if (!ast->left && !ast->right)
		return (create_execution_node(minishell, ast));	
	else
	{
		do_pipe(minishell, ast->left);		
		do_pipe(minishell, ast->right);
	}
/*
	else if (ast->left && is_state_active(ast->left->tokens->type, PIPE))
		return (do_pipe(minishell, ast->left));		
	else if (ast->right && is_state_active(ast->right->tokens->type, PIPE))
		return (do_pipe(minishell, ast->right));
	return (NULL);
*/
}

//
t_exec	*handle_operators(t_shel **minishell, t_tree *ast)
{
	t_exec	*node;

	node = NULL;
	if (is_state_active(ast->tokens->type, PIPE))	
		node = do_pipe(minishell, ast);
/*
	else if (is_state_active(ast->tokens->type, LAND))	
		node = do_and();
	else if (is_state_active(ast->tokens->type, LORR))	
		node =do_or();
*/
	return (node);
}

//
void	traverse_ast(t_shel **minishell, t_tree *ast, int *code, int *pipe)
{
	t_exec      *node;
    static int  original_std[2];

	node = NULL;
	if (!ast)
		return ;

	if (is_state_active(ast->tokens->type, PIPE | LAND | LORR))	
		node = handle_operators(minishell, ast);
/*
	else if (is_state_active(ast->tokens->type, OPAR))	
		node = handle_subshell(*minishell, ast);
*/
	else
	{
		node = create_execution_node(minishell, ast);
		execute_branch(*minishell, node, 0);
		free_execution_node(node);
		return ;
	}
	while (node)
	{
		printf("%s\n", *node->command);
		node = node->next;
	}
	//execute_command_line(node);
}
