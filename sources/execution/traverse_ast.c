/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 09:33:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int  execute_branch(t_shel *minishell, t_exec *node, int ctype)
{
    int             exit_code;
//	struct termios	tty_status;

    exit_code = -1;
	if (is_builtin(*node->command) && !(ctype & PIPE))
		return (exec_builtin(minishell, node));
	else
	{
		//save tty's params
//		tcgetattr(STDIN_FILENO, &tty_status);
		exit_code = create_child_process(minishell, node, ctype & PIPE);
//		tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);
	}
    return (exit_code);
}

/*
void    restore_stds(int original_std[2])
{
    dup2(STDIN_FILENO, original_std[0]);
    dup2(STDOUT_FILENO, original_std[1]);
}
*/

//
void	handle_operators(t_shel **minishell, t_tree *ast, t_exec **node)
{
	if (is_state_active(ast->tokens->type, PIPE))
		do_pipe(minishell, ast, node);
/*
	if (is_state_active(ast->tokens->type, PIPE | LAND | LORR))

	if (is_state_active(ast->tokens->type, PIPE | LAND | LORR))
*/
}

//
void	handle_simple_commands()
{

}

//
void	traverse_ast(t_shel **minishell, t_tree *ast, t_exec **node)
{
//    static int  original_std[2];
	t_exec	*head;

	if (!ast)
		return ;

	//Are we dealing with an operator ?
	if (is_state_active(ast->tokens->type, PIPE | LAND | LORR))
		handle_operators(minishell, ast, node);
	else
	{
		if (!*node)
			*node = create_execution_node(minishell, ast);
	//	else
			//Execute the current block;
	}

	*node ? printf("%s\n", *(*node)->command) : printf("NULL\n");
/*	
	//If not, are we dealing with a subshell ?
	else if (is_state_active(ast->tokens->type, OPAR))
		handle_subshell();
	//Simple command
	else
		handle_simple_command();
*/
/*

	if (is_amp_pipe(*ast->tokens->value))
	{
		set_state(pipe, INIT);
		if (is_state_active(ast->tokens->type, PIPE))
        {
            set_state(pipe, PIPE);
            original_std[0] = dup(STDIN_FILENO);
            original_std[1] = dup(STDOUT_FILENO);
        }
        else
        {
		    set_state(pipe, INIT);
            dup2(STDIN_FILENO, original_std[0]);  
            dup2(STDOUT_FILENO, original_std[0]);  
        }
	}

	traverse_ast(minishell, ast->left, code, pipe);

	if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
	{
		if (ast->tokens->type & OPAR)
		{
			//This function might need the int *code variable.
			//Also, we need to find a way to retrieve the subshell's content
			//int the parent.
			handle_subshell(*minishell, ast);
			return ;
		}

		node = create_execution_node(minishell, ast);
		if (!node || !node->command)
			return ;

		*code = execute_branch(*minishell, node, *pipe);

		if (*code == EXIT_STATUS)
			return ;


		set_error_code(minishell, *code);


		free_execution_node(node);
	}
	traverse_ast(minishell, ast->right, code, pipe);
*/
}
