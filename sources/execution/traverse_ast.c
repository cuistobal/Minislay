/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 10:50:03 by chrleroy         ###   ########.fr       */
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

/*
static int	do_and()
{

}

static int	do_or()
{

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
		node  = do_or();
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
static void	execute_branch(t_shell **minishell, t_tree *ast)
{
	t_exec	*node;
	t_tokn	*expands;
	t_tokn	*heredocs;
	t_tokn	*redirections;
	t_tokn	*assignations;

	node = NULL;
	expands = NULL;
	heredocs = NULL;
	redirections = NULL;

	assignations = create_token_sub_list(&ast->tokens, EQUL);
	if (assignations)
	{
		add_key_to_local(minishell, assignations);
		free_tokens(assignations);
	}
	expands = duplicate_token_list(ast->tokens);
	modify_redirections_nodes(&expands);
	expand(*minishell, &expands);
	expand(*minishell, &redirections);
	node = build_command_node(minishell, expands, &redirections);
	open_all_redirections(*minishell, node);
	execute_commands(minishell, node);
	free_execution_node(node);
}

//
void	traverse_ast(t_shell **minishell, t_tree *ast)
{
	int	original_stds[2];

	if (!ast)
		return ;

	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else
	{
		get_or_restore_stds(original_stds, true);
		execute_branch(minishell, ast);
		get_or_restore_stds(original_stds, false);
	}
	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
