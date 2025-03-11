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

//
//
//		MODIFICATION NEEDED BELOW	->	BOTH FUNCTION SHARE RESPONSIBILITY OR DO
//		THE SAME JOB.
//
//



static char	**initialise_execution(t_shel **minishell, t_tree *ast, t_tokn **redirections)
{
	int		count;
	char	**exec;
	t_tokn	*current;
	t_tokn	*expansions;
	t_tokn	*assignations;
	
	exec = NULL;
	expansions = NULL;
	assignations = NULL;
	current = ast->tokens;
	if (split_list(current, &assignations, &expansions))
	{

		//FIRST STEP	->	Expand the expansion list && indetify commands && 
		//					arguments. All WORDS following a redirection 
		//					operator is a filename. We then handle redirections
		
		if (expand(expansions))
		{
			modify_token_types(&expansions, redirections, &count);
			exec = get_command_and_arguments(expansions, count);
		}

		//SECOND STEP	->	Expand the assignation variables && append their
		//					newly assigned value to the right list (envp, local
		//					or command).

		expand(assignations);
		assign(assignations, expansions);	//We pass expansions because if we
											//have no command/redirections, the
											//assignations get sent to local.
	}
	return (exec);
}

//Entry point 
bool	traverse_and_execute(t_shel **minishell, t_tree *ast)
{
	char	**execution;
	t_tokn	*expansions;
	t_tokn	*redirections;
	t_tokn	*assignations;

	execution = NULL;
	expansions = NULL;
	redirections = NULL;
	assignations = NULL;
	if (*minishell && ast)
	{
		if (ast->tokens)
		{
			split_list(ast->tokens, &assignations, &expansions);	
			execution = initialise_execution(minishell, ast, &redirections);
				
		}
		//Identify type of command
		//
		//Turn the token list into redirs && char **exec
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
