#include "minislay.h"

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast)
{
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		//execute();
		if (ast->tokens)
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(*minishell, ast);
			else
			{
				prepare_for_exec(minishell, ast);	
				
			//	print_tokens(ast->tokens);
			}
		}
		traverse_ast(minishell, ast->right);
	}
	printf("vide\n");
}
