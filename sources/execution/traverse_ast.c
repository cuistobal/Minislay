#include "minislay.h"



//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast)
{
	char	**command;

	command = NULL;
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		if (ast->tokens)
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(*minishell, ast);
			else
			{
			//	prepare_for_exec(minishell, ast);	
				command = prepare_for_exec(minishell, ast);	
				if (command)
				{
					for (int  i = 0; command[i]; i++)
						printf("%s ", command[i]);
					printf("\n");
				}
//				create_process();	
//				execute(command);	
			//	print_tokens(ast->tokens);
			}
		}
		traverse_ast(minishell, ast->right);
	}
}
