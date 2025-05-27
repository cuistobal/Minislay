/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:42:25 by chrleroy         ###   ########.fr       */
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
static void	set_heredoc_name(char buffer[BUFFER_SIZE], char *limiter)
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
		buffer[index + 1] = 47 + i;
		i++;
	}
	if (i == 10)
		printf("Tu forces frere\n");
}

static void	open_heredocs(t_shell *minishell, t_exec **node, t_tokn **heredocs)
{
	t_exec	*head;
	t_tokn	*copy;
	char	name_buffer[BUFFER_SIZE];

	head = *node;
	copy = *heredocs;	
	while (copy)
	{	
		//if is_last heredoc for current node && is_last redire_in for current node 
		//	Use heredoc as input
		//else
		//	Unlink(heredoc) after appending content
		set_heredoc_name(name_buffer, copy->next->value);
		printf("%s ", name_buffer);
		move_pointer(&copy);
		move_pointer(&copy);
	}
	printf("\n");
}



//Ouvrir toutes els redirections
//Les loger dans le bon index
//POur els inredirs, unlink le heredoc s'il y a une nouvelle in_redir
static void	open_all_redirections(t_shell *minishell, t_tokn **heredocs, t_exec **node)
{
	int		index;
	t_tokn	*save;
	t_tokn	*htail;
	t_exec	*current;
	t_tokn	*redirections;

	index = 0;
	htail = NULL;
	current = *node;
	while (current)
	{
		redirections = (*node)->redirections[HERE_DOC];
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
	open_heredocs(minishell, node, heredocs);
}


void	split_redirections_and_commands(t_tokn	**src, t_tokn **cmd, t_tokn **r)
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

		copy = handle_assignations(minishell, &ast->tokens);

		split_redirections_and_commands(&ast->tokens, &command, &redirections);

		print_tokens(redirections);
		print_tokens(command);

		expand(minishell, command);	
		expand(minishell, command);	
		// Here, we create the execution lsit, regardless of the token types
	//	node = build_command_node(minishell, ast, &count);


		print_tokens(redirections);
print_tokens(command);
		// Now we need to get the redirection lists && open them


		// Finally, we execute the commands and free the nodes
		execute_commands(minishell, node, &count);
		free_execution_node(node);
	}

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
