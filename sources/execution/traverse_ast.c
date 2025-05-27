/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:52:37 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	handle_operators(t_shell **minislay, t_tree *ast)
{
	return ;
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
void	modify_redirections_nodes(t_tokn **source)
{
	t_tokn	*prev;
	t_tokn	*next;
	t_tokn	*copy;

	prev = NULL;
	copy = *source;
	while (copy)
	{
		next = copy->next;
		if (valid_lexeme(copy, HDOC, ARED))
		{
			if (is_state_active(copy->type, HDOC))
				set_state(&copy->next->type, HDOC);
			if (is_state_active(copy->type, IRED))
				set_state(&copy->next->type, IRED);
			if (is_state_active(copy->type, ORED))
				set_state(&copy->next->type, ORED);
			if (is_state_active(copy->type, ARED))
				set_state(&copy->next->type, ARED);
			if (!prev)
			{
				free(*source);
				*source = next;
				copy = *source;
			}
			else
			{
				prev->next = next;
				free(copy);
				copy = next;
			}	
		}	
		prev = copy;
		move_pointer(&copy);
	}
}

void	execute_branch(t_shell **minishell, t_tree *ast)
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

	//First, we handle redirections and return a token list containing only
	//commands and redirections

	assignations = create_token_sub_list(&ast->tokens, EQUL);
	//Liste idnependante -> ne pas oublier de la free

	expands = duplicate_token_list(ast->tokens);

	modify_redirections_nodes(&expands);

	expand(*minishell, &expands);
	expand(*minishell, &redirections);

	node = build_command_node(minishell, expands, &redirections);

	open_all_redirections(*minishell, &redirections, &heredocs);	

	// Finally, we execute the commands and free the nodes
	execute_commands(minishell, node);
	free_execution_node(node);
}

//
void	traverse_ast(t_shell **minishell, t_tree *ast)
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
	if (!ast)
		return ;

	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else	
		execute_branch(minishell, ast);

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
