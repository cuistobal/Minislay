/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 11:35:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	execute_command(char **commands, char **env)
{
	char	*command;
	char	**arguments;

	command = *commands;
	arguments = commands;
//test
	pid_t	pid = fork();
	if (pid == 0) 
	{
		exit(execve(command, arguments, env));
	}

}

//
void	traverse_ast(t_shel **minishell, t_tree *ast)
{
	t_exec			*node;
	struct termios	tty_status;

	if (!ast)
		return ;
	traverse_ast(minishell, ast->left);
	if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
	{
		if (ast->tokens->type & OPAR)
		{
			handle_subshell(*minishell, ast);
			return ;
		}

		node = create_execution_node(minishell, ast);

		if (is_builtin(*node->command) && !(ast->tokens->type & PIPE))
	//		exec_builtin(node->command, node->environ, minishell);
			exec_builtin(minishell, &node);
		else
		{
			//save tty's params

			tcgetattr(STDIN_FILENO, &tty_status);

			create_child_process(*minishell, &node);

			tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);

			//restore tty's params
		}
		free_execution_node(&node);
	}
	traverse_ast(minishell, ast->right);
}
