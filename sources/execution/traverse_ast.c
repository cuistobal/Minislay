/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 11:21:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	execute_command(char **commands, char **env)
{
	char	*command;
	char	**arguments;

	command = *commands;
	arguments = commands;
	pid_t	pid = fork();
	if (pid == 0)
		exit(execve(command, arguments, env));
}

//
static int  execute_branch(t_shel *minishell, t_exec *node, int ctype)
{
    int             exit_code;
	struct termios	tty_status;

    exit_code = -1;
	if (is_builtin(*node->command) && !(ctype & PIPE))
		return (exec_builtin(minishell, node));
	else
	{
		//save tty's params
		tcgetattr(STDIN_FILENO, &tty_status);
		exit_code = create_child_process(minishell, node, ctype & PIPE);
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);
	}
    return (exit_code);
}

//
void	traverse_ast(t_shel **minishell, t_tree *ast, int *code, int *pipe)
{
	t_exec  *node;

	node = NULL;
	if (!ast)
		return ;

	if (is_amp_pipe(*ast->tokens->value))
	{
		set_state(pipe, INIT);
		if (is_state_active(ast->tokens->type, PIPE))
			set_state(pipe, PIPE);
	}

	traverse_ast(minishell, ast->left, code, pipe);

	if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
	{
		if (ast->tokens->type & OPAR)
		{
			handle_subshell(*minishell, ast);
			return ;
		}

		node = create_execution_node(minishell, ast);
		if (!node || !node->command)
			return ;

		*code = execute_branch(*minishell, node, *pipe);

		if (*code == EXIT_STATUS)
			return ;

		/*	This function needs to be renamed	*/
		set_error_code(minishell, *code);
		/*										*/

		free_execution_node(node);
	}
	traverse_ast(minishell, ast->right, code, pipe);
}
