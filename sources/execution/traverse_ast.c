#include "minislay.h"

void	traverse_ast(t_shel *minishell, t_tree *ast)
{
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		//execute();
		if (ast->tokens)
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(minishell, ast);
			else
			{
				prepare_for_exec(ast);	
				while (ast->tokens)
				{
					printf("%s %d	", ast->tokens->value, ast->tokens->type);
					ast->tokens = ast->tokens->next;
				}
				printf("\n");
			}
		}
		traverse_ast(minishell, ast->right);
	}
}
