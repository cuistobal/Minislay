#include "minislay.h"

static bool	handle_assignations(t_shel *minishell, t_tokn *token)
{
	char	*key;	
	char	*value;
	char	*assignation;

	if (token)
	{
		assignation = token->value;
		if (assignation)
		{
			key = assignation;
			value = strtok_r(assignation, "=", NULL);
			

			find_key();
		}
}
