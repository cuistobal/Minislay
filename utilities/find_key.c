#include "minislay.h"

//
static bool	find_key_in_avlt(t_avlt *tree, char **value, char *key)
{
	t_avlt	*node;

	node = NULL;
	if (tree)
	{
		printf("coucouuuuuuuuuuu\n");
		find_element(tree, &node, *value, key);
		if (node)
		{
			*value = node->data[VALUE];
			return (true);
		}
	}
	return (false);
}

//
static bool	find_key_in_local(t_env *local, char **value, char *key)
{
	while (local)
	{
		if (strcmp(local->var[KEY], key) == 0)
		{
			*value = local->var[VALUE];
			return (true);
		}
		move_env_pointer(&local);
	}
	return (false);
}

//
static bool	find_key_in_command(t_env *command, char **value, char *key)
{
	while (command)
	{
		if (strcmp(command->var[KEY], key) == 0)
		{
			*value = command->var[VALUE];
			return (true);
		}
		move_env_pointer(&command);
	}
	return (false);
}

//Looking for the $KEY, so we can acess its value. If $KEY isn't found, we 
//return false;
bool	find_key(t_shel *minishell, char **value, char *key)
{
	if (minishell)
	{
		if (!find_key_in_avlt(minishell->expt, value, key))
		{
			if (!find_key_in_local(minishell->local, value, key))
			{
				return (find_key_in_command(minishell->command, value, key));
			}
		}
	}
	return (false);
}
