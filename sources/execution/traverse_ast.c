/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 09:48:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
//
static int	execute_branch(t_shell **minishell, t_tree *ast)
{
	int		ret;
	int		count;
	t_exec	*node;
	t_tokn	*expands;

    count = 0;
	node = NULL;
	expands = NULL;
	modify_redirections_nodes(&ast->tokens);
	expand(*minishell, &ast->tokens);
	node = build_command_node(minishell, ast->tokens, &count); 
    (*minishell)->execution = node;
	open_all_redirections(*minishell, node);
	ret = execute_commands(minishell, node, count);
    append_exit_code(*minishell, ret, true);
	free_execution_node(node);
	return (ret);
}

static int  handle_logical_operators(t_shell **minishell, t_tree *ast)
{
    int ret;

    if (is_state_active(ast->tokens->type, LAND))
    {
        free_tokens(ast->tokens);
        ret = traverse_ast(minishell, ast->left);
        if (ret == 0)
            return (traverse_ast(minishell, ast->right));
        return (free_tokens(ast->right->tokens), free_tree(ast->right), \
					ast->right = NULL, ret);
    }
    else if (is_state_active(ast->tokens->type, LORR))
    {
        free_tokens(ast->tokens);
        ret = traverse_ast(minishell, ast->left);
        if (ret != 0)
            return (traverse_ast(minishell, ast->right));
        return (free_tokens(ast->right->tokens), free_tree(ast->right), \
					ast->right = NULL, ret);
    }
    else
    {      
        ret = handle_subshell(*minishell, ast);
        free_tokens(ast->tokens);
    }
    return (ret);
}


//
int	traverse_ast(t_shell **minishell, t_tree *ast)
{
    int	ret;
    int	original_stds[2];

    if (!ast)
        return (SUCCESS);
	ret = 0;
    if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
      turn (handle_logical_operators(minishell, ast));
    else
    {
        get_or_restore_stds((*minishell)->original_stds, true);
        ret = execute_branch(minishell, ast);
        get_or_restore_stds((*minishell)->original_stds, false);
    }
    return (ret);
}
