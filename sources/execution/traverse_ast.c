#include "minislay.h"

void	traverse_ast(t_shel *minishell, t_tree *ast)
{
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		//execute();
		if (ast->tokens->type & OPAR)
			handle_subshell(minishell, ast);
		else
		{
			while (ast->tokens)
			{
				printf("%s ", ast->tokens->value);
				ast->tokens = ast->tokens->next;
			}
			printf("\n");
		}
		traverse_ast(minishell, ast->right);
	}
}
