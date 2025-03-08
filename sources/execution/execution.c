#include "minislay.h"

static bool	traverse_and_execute(t_shel **minishell, t_tree *ast)
{
	char	**execution;

	if (ast)
	{
		//Identify type of command
		//
		//Turn the token list into redirs && char **exec
	}
}

bool	execution(t_shel **minishell, t_tree *ast)
{
	if (*minishell && ast)
	{
		traverse_and_execute(minishell, ast);		
	}
}
