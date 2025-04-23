#include "minislay.h"

static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};

//static bool	is_builtin(char *command)
static	bool is_builtin(char *command)
{
	int	index;

	index = 0;
	if (!command || !*command)
		return (false);
	while (index < BCNT)
	{
		if (strcmp(command, g_b[index]) == 0)
			break;
		index++;
	}
	return (index < BCNT);
}

//
static bool	is_absolute(char *command)
{
	return (command && *command && *command == '/');
}

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shel *minishell, t_tokn *list, int count)
{
	int		index;
	char	**commands;

	index = 0;
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	if (!commands)
		return (NULL);
	while (list)
	{
		if (index == 0)
		{
			if (!is_builtin(list->value) && !is_absolute(list->value))
			{
				if (!retrieve_path(minishell, &list->value))
				{
					printf("No path for command %s\n", list->value);	
					return (NULL);
				}
			}
			/*
			{
			//		free_array(commands, count);
			//		break ;
				printf("No path for command %s\n", list->value);	
			}
			*/
		}
		commands[index] = list->value;
		move_pointer(&list);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}
