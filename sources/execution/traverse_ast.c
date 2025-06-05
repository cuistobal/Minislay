/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/05 14:25:42 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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
static int	execute_branch(t_shell **minishell, t_tree *ast)
{
	int		ret;
	int		count;
	t_exec	*node;
	t_tokn	*expands;
	t_tokn	*assignations;

    count = 0;
	node = NULL;
	expands = NULL;
	assignations = create_token_sub_list(&ast->tokens, EQUL);
	if (assignations)
	{
		add_key_to_local(minishell, assignations);
		free_tokens(assignations);
	}
	modify_redirections_nodes(&ast->tokens);
	expand(*minishell, &ast->tokens);
	node = build_command_node(minishell, ast->tokens, &count); 
	open_all_redirections(*minishell, node);
	ret = execute_commands(minishell, node, count);
    append_exit_code(*minishell, ret, true);
	free_execution_node(node);
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
    if (is_state_active(ast->tokens->type, LAND))
    {
        ret = traverse_ast(minishell, ast->left);
        if (ret == 0)
            return (traverse_ast(minishell, ast->right));
    }
    else if (is_state_active(ast->tokens->type, LORR))
    {
        ret = traverse_ast(minishell, ast->left);
        if (ret != 0)
            return (traverse_ast(minishell, ast->right));
    }
    else if (is_state_active(ast->tokens->type, OPAR))
        return handle_subshell(*minishell, ast);
    else
    {
        get_or_restore_stds(original_stds, true);
        ret = execute_branch(minishell, ast);
        get_or_restore_stds(original_stds, false);
    }
    return (ret);
}
