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

/*
static void	execute_command(t_shel **minishell, char **command)
{
	pid_t	pid;

	if (!command)
		return ;
	if (**command == '/')
		pid = create_process();	
}
*/

static void	quote_removal_helper(char *token, char *removed)
{
	int		save;
	int		index;
	char	quote;

	save = 0;
	index = 0;
	quote = INIT;
	while (token[index])
	{
		if (!quote)
		{
			if (is_quote(token[index]))
				quote = token[index];
			else
				removed[save++] = token[index];
		}
		else
		{
			if (token[index] == quote)
				quote = INIT;
			else
				removed[save++] = token[index];
		}
		index++;
	}
}

//
static bool	quote_removal(t_tokn *list)
{
	int		tlen;
	char	*removed;

	while (list)
	{
		tlen = (int)strlen(list->value);
		removed = (char *)malloc(sizeof(char) * tlen);
		if (!removed)
			return (false);
		memset(removed, 0, tlen);
		quote_removal_helper(list->value, removed);
		free(list->value);
		list->value = removed;
		list = list->next;	
	}
	return (true);
}
//
static char	**initialise_execution(t_shel *minishell, t_tokn **redirections, t_tokn **expansions)
{
	int		count;
	t_tokn	*copy;

	count = 0;

	modify_token_types(expansions, redirections, &count);

	copy = *expansions;
	
	if (!expand(minishell, &copy))
		return (NULL);

	if (!quote_removal(*expansions))
		return (NULL);
	
	handle_redirection_list(minishell, redirections);

	return (get_command_and_arguments(minishell, *expansions, count));
}

//Entry point -> Needs some rework
//
//	Either:
//	
//		-> 	Fix the misleading name
//		->	Change the return type to char**
//
//bool	prepare_for_exec(t_shel **minishell, t_tree *ast)
char	**prepare_for_exec(t_shel **minishell, t_tree *ast)
{
	char	**command;
	t_tokn	*expansions;
	t_tokn	*redirections;
	t_tokn	*assignations;

	command = NULL;
	expansions = NULL;
	redirections = NULL;
	assignations = NULL;
	if (!*minishell && !ast)
		return (NULL);

	if (!ast->tokens)	
		return (NULL);
	split_list(ast->tokens, &assignations, &expansions);

	//perform expansions
			
	//print_tokens(expansions);

	command = initialise_execution(*minishell, &redirections, &expansions);
				
	//print_tokens(redirections);
	//print_tokens(expansions);

	//Redirections belong there

	//expand redirections

	print_exec(assignations, expansions, redirections, command);

	//execve(*execution, execution + 1, NULL);

//	if (!expand(*minishell, &assignations))
//		return (NULL);

	print_tokens(assignations);
	
//	execute_command(minishell, command);

	//Identify type of command
	//
	//Turn the token list into redirs && char **exec
	return (command);
}
