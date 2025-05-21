/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 09:48:30 by chrleroy         ###   ########.fr       */
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
static bool	set_heredoc_name(char buffer[BUFFER_SIZE], char *limiter)
{
	int	i;
	int	index;
	int	limlen;
	
	i = 0;
	memset(buffer, 0, BUFFER_SIZE);
	index = strlen(HEREDOC);
	strncpy(buffer, HEREDOC, index);
	limlen = strlen(limiter);
	strncpy(buffer + index, limiter, limlen);
	index += limlen;
	while (access(buffer, F_OK) == 0 && i < 10)
	{
		buffer[index] = 48 + i;
		i++;
	}
	return (i < 10);
/*
	if (i == 10)
		printf("Tu forces frere\n");
*/
}

static int open_heredocs(t_shell *minishell, t_tokn **heredocs)
{
	t_tokn	*copy;
	char	name_buffer[BUFFER_SIZE];

	copy = *heredocs;	
	while (copy)
	{	
		//if is_last heredoc for current node && is_last redire_in for current node 
		//	Use heredoc as input
		//else
		//	Unlink(heredoc) after appending content
		if (!set_heredoc_name(name_buffer, copy->next->value))
			return (GENERAL_ERROR);
		copy->value = name_buffer;
		open_heredocs(minishell, &copy);
/*
		move_pointer(&copy);
		move_pointer(&copy);
*/
	}
	printf("\n");
}



//Ouvrir toutes els redirections
//Les loger dans le bon index
//POur els inredirs, unlink le heredoc s'il y a une nouvelle in_redir
static int	open_all_redirections(t_shell *minishell, t_tokn **heredocs, t_tokn **redirections)
{
	int		index;
	t_tokn	*save;
	t_tokn	*htail;
	t_tokn	*current;

	index = 0;
	htail = NULL;
	current = *redirections;
	while (current)
	{
		if (current->type & HDOC)
			insert_heredoc_in_list(heredocs, &htail, current);		
		else if (current->type & IRED)
			open_infile(&current);
		else if (current->type & ORED)
			open_outfile(&current);
		else if (current->type & ARED)
			open_outfile_append(&current);
		move_pointer(&current);
		move_pointer(&current);
	}
	if (htail)
		htail->next = NULL;
	return (open_heredocs(minishell, heredocs));
}


static void	split_redirections_and_commands(t_tokn	**src, t_tokn **cmd, t_tokn **r)
{
	t_tokn	*copy;
	t_tokn	*rtail;
	t_tokn	*ctail;

	rtail = NULL;	
	ctail = NULL;
	copy = *src;
	while (copy)
	{
		if (valid_lexeme(copy, IRED, ARED))
		{
			append_token_list(r, &rtail, copy);
			move_pointer(&copy);
			append_token_list(r, &rtail, copy);
		}
		else
			append_token_list(cmd, &ctail, copy);
		move_pointer(&copy);
	}
	if (rtail)
		rtail->next = NULL;
	if (ctail)
		ctail->next = NULL;
}

//
void	traverse_ast(t_shell **minishell, t_tree *ast)
{
	int		count;
	t_exec	*node;
	t_tokn	*copy;
	t_tokn	*command;
	t_tokn	*redirections;	
	t_tokn	*heredocs;

	node = NULL;
	command = NULL;
	redirections = NULL;
	heredocs = NULL;
	if (!ast)
		return ;

	if (is_state_active(ast->tokens->type, LAND | LORR | OPAR))
		handle_operators(minishell, ast);
	else	
	{
		//First, we handle redirections and return a token list containing only
		//commands and redirections

		copy = handle_assignations(minishell, &ast->tokens);

		//Then, we split this list into 2 sublists
		split_redirections_and_commands(&ast->tokens, &command, &redirections);

		//Now, we expand those lists according to bash's priorities
		expand(*minishell, &command);
		expand(*minishell, &redirections);


		//We open all redirections and retrieve the heredocs content;

		open_all_redirections(*minishell, &heredocs, &redirections);

		// Now we can create all the execution nodes and append their redirections
		node = build_command_node(minishell, ast, &count);

		// Finally, we execute the commands and free the nodes
		execute_commands(minishell, node, &count);
		free_execution_node(node);
	}

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
