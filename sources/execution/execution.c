#include "minislay.h"

/*			OLD VERSION
 *
 *
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
}*/

//
static char	**initialise_execution(t_shel *minishell, t_tokn **redirections, t_tokn **expansions)
{
	int		count;
	t_tokn	*copy;

	copy = *expansions;
	/*
	expand(minishell, &copy);
	modify_token_types(expansions, redirections, &count);
	return (get_command_and_arguments(*expansions, count));
	*/
	if (expand(minishell, &copy))
	{
		modify_token_types(expansions, redirections, &count);
		return (get_command_and_arguments(*expansions, count));
	}
	return (NULL);
}

//Entry point 
bool	prepare_for_exec(t_shel **minishell, t_tree *ast)
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

			execution = initialise_execution(*minishell, &redirections, &expansions);

			print_exec(assignations, expansions, redirections, execution);

			if (expand(*minishell, &assignations))
					print_tokens(assignations);
			
			//assign(*minishell, assignations);
		}
		//Identify type of command
		//
		//Turn the token list into redirs && char **exec
		return true;
	}
	return false;
}
