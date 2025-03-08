#include "minislay.h"

static bool	find_key_in_env(t_shel **minishell, char *key, char *value)
{
	if (*minishell)
	{

	}
}

static void	find_matching_key(t_shel **minishell, char *key, char *value)
{
	if (minishell)
	{
		if (key && value)
		{
			if (!find_key_in_env())
				find_key_in_local();

		}
		printf("Invalid key or value.\n");
	}
	printf("Invalid minishell.\n");
}

bool	handle_assignations(t_shel **minishell, t_tokn *current)
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
	return (false);
}
