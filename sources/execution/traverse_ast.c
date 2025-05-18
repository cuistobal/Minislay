/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 16:56:43 by chrleroy         ###   ########.fr       */
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

static void	open_heredocs(t_tokn **heredocs)
{
	t_tokn	*copy;

	copy = *heredocs;	
	while (copy)
	{
//open here_doc();
		copy = copy->next;
	}
}



static void	open_all_redirections(t_tokn **heredocs, t_exec **node, t_shell *minishell)
{
	int		index;
	t_tokn	*save;
	t_tokn	*htail;
	t_exec	*current;
	t_tokn	*redirections;

	index = 0;
	htail = NULL;
	current = *node;
	save = current->redirections[HERE_DOC];
	print_tokens(save);
	while (current)
	{
		redirections = (*node)->redirections[HERE_DOC];
		//redirections = redir;
		while (redirections)
		{
			if (redirections->type & HDOC)
				insert_heredoc_in_list(heredocs, &htail, redirections);		
			else if (redirections->type & IRED)
				open_infile(&redirections);
			else if (redirections->type & ORED)
				open_outfile(&redirections);
			else if (redirections->type & ARED)
				open_outfile_append(&redirections);

		}
		current = current->next;
		index++;	
	}
}

//
void	traverse_ast(t_shell **minishell, t_tree *ast)
{
	int			count;
	t_exec      *node;
	t_tokn		*heredocs;

	count = 0;
	node = NULL;
	heredocs = NULL;
	if (!ast)
		return ;

	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else	
	{
		node = build_command_node(minishell, ast, &count);
		//Split redirections form heredocs
		//OPen all heredocs
		//
		open_all_redirections(&heredocs, &node, *minishell);		
		open_heredocs(&heredocs);

		execute_commands(minishell, node, &count);
		free_execution_node(node);
	}

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
