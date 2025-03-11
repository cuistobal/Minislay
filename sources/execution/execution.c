#include "minislay.h"

/*
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
}*/

static char	**initialise_execution(t_shel **minishell, t_tree *ast, t_tokn *list)
{
	char	**execution;
	t_tokn	*expansions;
	t_tokn	*assignations;

	execution = NULL;
	expansions = NULL;
	assignations = NULL;
	if (split_list(list, &assignations, &expansions))
	{
		//FIRST STEP	->	Expand the expansion list && indetiy commands && 
		//					arguments. All WORDS following a redirection 
		//					operator is a filename. We then handle redirections
		if (expand(expansions))
		{
			command = handle_commands(expansions);
			if (command)
				handle_redirections(expansions);
		}
		//SECOND STEP	->	Expand the assignation variables && append their
		//					newly assigned value to the right list (envp, local
		//					or command).
		expand(assignations);
		assign(assignations, expansions);
	}
	return (execution);
}

//Entry point 
bool	traverse_and_execute(t_shel **minishell, t_tree *ast)
{
	t_tokn	*current;
	t_tokn	*expansions;
	t_tokn	*assignations;
	char	**execution;

	if (*minishell && ast)
	{
		if (ast->tokens)
		{
			current = ast->tokens;
			initialise_execution(minishell, ast, current);
			split_list(current, &assignations, &expansions);	
			expand(expansions);
                
		//	print_tokens(assignations);
        //	print_tokens(expansions);
				
			handle_assignations(minishell, current);
			current = current->next;
		}
		//Identify type of command
		//
		//Turn the token list into redirs && char **exec
		}
	}
}




/*
bool	execution(t_shel **minishell, t_tree *ast)
{
	if (*minishell && ast)
	{
		traverse_and_execute(minishell, ast);		
	}
}*/
