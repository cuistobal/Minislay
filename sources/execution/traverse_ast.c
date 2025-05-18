/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 15:34:19 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
static int  execute_branch(t_shell *minishell, t_exec **node)
{
	if (is_builtin(*(*node)->command))
		return (exec_builtin((*node)->command, (*node)->environ, minishell));
	return (create_child_process(minishell, node));
}
*/

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

/*
void	free_tree_node(t_tree *node)
{
	if (!node)
		return ;
	if (node->tokens)
	{
		free_tokens(node->tokens);
		node->tokens = NULL;
	}
	node->left = NULL;
	node->right = NULL;
	free(node);
	node = NULL;
}
*/
//
void	traverse_ast(t_shell **minishell, t_tree *ast)
{
	int			count;
//	int			std[2];
	t_exec      *node;

	count = 0;
	node = NULL;

	if (!ast)
		return ;

//	std[0] = dup(STDIN_FILENO);
//	std[1] = dup(STDOUT_FILENO);

	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else	
	{
		node = build_command_node(minishell, ast, &count);
		open_heredocs();	
		execute_commands(minishell, node, &count);
		free_execution_node(node);
	}

//	dup2(std[0], STDIN_FILENO);
//	dup2(std[1], STDOUT_FILENO);

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
