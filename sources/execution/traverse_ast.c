#include "minislay.h"

void	traverse_ast(t_shel *minishell, t_tree *ast)
{
	if (ast)
	{
		if (ast->tokens->type & OPAR)
		{
			handle_subshell(minishell, ast);
		}
		traverse_ast(minishell, ast->left);
		//execute();
		printf("Malcolm\n");
		traverse_ast(minishell, ast->right);
	}
}
