#include "minislay.h"

//
bool	handle_assignations(t_shel *minishell, t_tokn *token)
{
	char	*key;	
	char	*value;
	char	*assignation;

	if (token && token->value)
	{
		assignation = strdup(token->value);		//We need to keep the original memory intact
		if (assignation)
		{
			key = assignation;
			strtok_r(assignation, "=", &value); //Remove this magic number	
			


		}
	}
}
