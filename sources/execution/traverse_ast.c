/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 16:10:45 by chrleroy         ###   ########.fr       */
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
static int	handle_operators(t_shell **minishell, t_tree *ast)
{
	return 0;	

	if (is_state_active(ast->tokens->type, OPAR))
		return (handle_subshell(*minishell, ast));
	else if (is_state_active(ast->tokens->type, LAND))
		return (LAND);
	return (LORR);
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
static int	execute_branch(t_shell **minishell, t_tree *ast)
{
	int		ret;
	int		count;
	t_exec	*node;
	t_tokn	*expands;
	t_tokn	*assignations;

	node = NULL;
	expands = NULL;
	assignations = create_token_sub_list(&ast->tokens, EQUL);
	if (assignations)
	{
		add_key_to_local(minishell, assignations);
		free_tokens(assignations);
	}
	expands = duplicate_token_list(ast->tokens);
	modify_redirections_nodes(&expands);
	expand(*minishell, &expands);
	node = build_command_node(minishell, expands, &count); 
	open_all_redirections(*minishell, node);
	ret = execute_commands(minishell, node, count);
	free_execution_node(node);
	return (ret);
}

//
int	traverse_ast(t_shell **minishell, t_tree *ast)
{
	int	ret;
	int	ctype;
	int	original_stds[2];

	if (!ast || !ast->tokens)
		return (SUCCESS);
	ctype = 0;
	if (is_state_active(ast->tokens->type, OPAR))
		handle_subshell(*minishell, ast);
	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		ctype = handle_operators(minishell, ast);
	else
	{
		get_or_restore_stds(original_stds, true);
		ret = execute_branch(minishell, ast);
		get_or_restore_stds(original_stds, false);
	}	
	if (ret == EXIT_CODE)
		return (EXIT_CODE);
	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);
	return (SUCCESS);
}
