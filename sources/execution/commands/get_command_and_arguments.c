#include "minislay.h"

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_tokn *list, int count)
{
	int		index;
	char	**commands;

	index = 0;
	commands = (char **)malloc(sizeof(char *) * count);
	if (commands)
	{	
		while (list)
		{
			commands[index] = list->value;
			move_pointer(&list);
			index++;
		}
		commands[index] = NULL;
	}
	return (commands);
}
