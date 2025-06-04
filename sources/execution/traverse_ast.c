/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/03 07:26:36 by cuistobal        ###   ########.fr       */
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
	modify_redirections_nodes(&ast->tokens);
	expand(*minishell, &ast->tokens);
	node = build_command_node(minishell, ast->tokens, &count); 
	open_all_redirections(*minishell, node);
	ret = execute_commands(minishell, node, count);
	free_execution_node(node);
	return (ret);
}

static bool	should_i_go_on(int ctype, int ret)		
{
	if (ctype == LAND && ret != 0)
		return (false);
	if (ctype == LORR && ret == 0)
		return (false);
	return (true);
}

//
int	traverse_ast(t_shell **minishell, t_tree *ast)
{
    int	ret = 0;
    int	ctype = 0;
    int	original_stds[2];

    if (!ast || !ast->tokens)
        return (SUCCESS);

    // Détection du type d'opérateur
    if (is_state_active(ast->tokens->type, OPAR))
        return (handle_subshell(*minishell, ast));

    if (is_state_active(ast->tokens->type, LAND | LORR))
        ctype = ast->tokens->type;
    
    get_or_restore_stds(original_stds, true);
    ret = execute_branch(minishell, ast);
    get_or_restore_stds(original_stds, false);

    // Gestion des opérateurs && et ||
    if (ctype == LAND && ret == 0)
        return traverse_ast(minishell, ast->right);
    if (ctype == LORR && ret != 0)
        return traverse_ast(minishell, ast->right);

    // Parcours récursif classique si pas d'opérateur logique
    traverse_ast(minishell, ast->left);
    traverse_ast(minishell, ast->right);
    return (ret);
}

/*
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

//
// 	if (ret == EXIT_CODE)
// 		return (EXIT_CODE);
// //	else if (ctype != 0)
// //	{
// 		ret = traverse_ast(minishell, ast->left);
// 		if (should_i_go_on(ctype, ret))
// 			return (traverse_ast(minishell, ast->right));
// 		return (ret);
// //	}
//
	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);
	return (ret);
}
*/
