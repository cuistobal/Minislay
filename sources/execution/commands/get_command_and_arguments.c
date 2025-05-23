/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:08:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/24 14:00:26 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shell *minishell, t_tokn *list)
{
	int		count;
	int		index;
    char    *copy;
	char	**commands;

	index = 0;
	commands = (char **)calloc(TAB_SIZE, sizeof(char *));
	if (!commands)
		return (NULL);
	while (list)
	{
        copy = strdup(list->value);
		if (index == 0)
		{
			if (!is_builtin(copy) && !is_absolute(copy))
			{
				if (!is_executable(copy))
				{
					if (!retrieve_path(minishell, &copy))
						return (error_message("Invalid command\n"), NULL);
				}
			}
		}
		commands[index] = copy;
		move_pointer(&list);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}
