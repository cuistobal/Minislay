/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 18:15:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	execute_branch(t_shel *minishell, t_exec *node, int ctype)
{
	struct termios	tty_status;

	if (is_builtin(*node->command) && !(ctype & PIPE))
	//		exec_builtin(node->command, node->environ, minishell);
		exec_builtin(minishell, node);
	else
	{
		//save tty's params

			tcgetattr(STDIN_FILENO, &tty_status);
	//		tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);

			create_child_process(minishell, node);

			tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);
	}
}

//
void	traverse_ast(t_shel *minishell, t_tree *ast)
{
	t_exec			*node;
	struct termios	tty_status;

	node = NULL;
	if (!ast)
		return ;
	traverse_ast(minishell, ast->left);
	if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
	{
		if (ast->tokens->type & OPAR)
		{
			handle_subshell(minishell, ast);
			return ;
		}

		node = create_execution_node(minishell, ast);
		if (!node)
			return ;

		execute_branch(minishell, node, ast->tokens->type);

		free_execution_node(node);
	}
	traverse_ast(minishell, ast->right);
}
