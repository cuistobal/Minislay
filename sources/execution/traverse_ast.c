/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/24 15:31:35 by cuistobal        ###   ########.fr       */
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


/*
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
\\	if (i == 10)
\\		printf("Tu forces frere\n");

}

static int open_heredocs(t_shell *minishell, t_tokn *heredocs)
{
	t_tokn	*copy;
	char	name_buffer[BUFFER_SIZE];

	copy = heredocs;	
	while (copy)
	{
		if (!copy->next)
			return (GENERAL_ERROR);
		//if is_last heredoc for current node && is_last redire_in for current node 
		//	Use heredoc as input
		//else
		//	Unlink(heredoc) after appending content
		if (!set_heredoc_name(name_buffer, copy->next->value))
			return (GENERAL_ERROR);
		free(copy->value);
		copy->value = strdup(name_buffer);
		handle_here_doc(minishell, copy);
		move_pointer(&copy);
		move_pointer(&copy);
	}
}
*/

//
static void	split_redirections_and_commands(t_tokn *copy, t_tokn **cmd, t_tokn **r)
{
	t_tokn	*rtail;
	t_tokn	*ctail;

	rtail = NULL;	
	ctail = NULL;
	while (copy)
	{
		if (valid_lexeme(copy, HDOC, ARED | OPAR))
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
/*
		if (valid_lexeme(copy, HDOC, ARED))
		{
			free(copy->value);
			copy->value = next->value;
			copy->next = next->next;
			free(next);
		}
*/
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
	{
		//First, we handle redirections and return a token list containing only
		//commands and redirections

		assignations = create_token_sub_list(&ast->tokens, EQUL);
		//Liste idnependante -> ne pas oublier de la free

		expands = duplicate_token_list(ast->tokens);

		modify_redirections_nodes(&expands);

		expand(*minishell, &expands);
		expand(*minishell, &redirections);

		node = build_command_node(minishell, expands, &redirections);


//open_all_redirections()

        t_exec  *copy = node;
        t_exec  *save = NULL;

        while (copy)
        {
            while (copy->redirections)
            {
                if (is_state_active(copy->redirections->type, HDOC))
                {
                    if (save)
                        unlink(save->redirections->value);
                    handle_here_doc(*minishell, copy->redirections);
                    save = copy;
                }
                move_pointer(&copy->redirections);
            }
            copy = copy->next;
        }
        
	//	open_all_redirections(*minishell, &redirections, &heredocs);
		
//		matchmaking(&node, &redirections, &heredocs)

		// Finally, we execute the commands and free the nodes
		execute_commands(minishell, node);
		free_execution_node(node);

	}

	traverse_ast(minishell, ast->left);
	traverse_ast(minishell, ast->right);

//	free_tree_node(ast);
}
