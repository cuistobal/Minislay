#include "minislay.h"

static void	handle_assignations(t_shel **minishell, t_tokn *current)
{
	char	*key;
	char	*value;
	char	*assignation;

	if (current)
	{
		assignation = strdup(current->value);
		if (assignation)
		{
			key = assignation;
			strtok_r(key, "=", &value);
			find_matching_key();
		}
	}
}

static bool	traverse_and_execute(t_shel **minishell, t_tree *ast)
{
	t_tokn	*current;
	char	**execution;

	if (ast)
	{
		if (ast->tokens)
		{
			current = ast->tokens;
			while (is_state_active(current->type, EQUL))
			{
				handle_assignations(minishell, current);
				current = current->next;
			}
		//Identify type of command
		//
		//Turn the token list into redirs && char **exec
		}
	}
}

bool	execution(t_shel **minishell, t_tree *ast)
{
	if (*minishell && ast)
	{
		traverse_and_execute(minishell, ast);		
	}
}
