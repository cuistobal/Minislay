#include "minislay.h"

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shel *minishell, t_tokn *list, int count)
{
	int		index;
	char	**commands;

	index = 0;
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	if (commands)
	{	
		while (list)
		{
			if (index == 0 && command_type(list->value))
			{
				if (!retrieve_path(minishell, &list->value))
				{
			//		free_array(commands, count);
			//		break ;
					printf("No path for command %s\n", list->value);	
				}
			}
			commands[index] = list->value;
			move_pointer(&list);
			index++;
		}
		commands[index] = NULL;
	}
	return (commands);
}
