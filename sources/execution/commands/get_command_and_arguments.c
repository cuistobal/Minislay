/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:08:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:55:28 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shell *minishell, t_tokn *list)
{
	int		count;
	int		index;
	char	**commands;

	count = 1;
	index = 0;
	commands = (char **)calloc(count + 1, sizeof(char *));
	if (!commands)
		return (NULL);
	while (list)
	{
		if (index == 0 && !is_builtin(list->value) && !is_absolute(list->value))
		{
			if (!is_executable(list->value) && !retrieve_path(minishell, &list->value))
			{
				free_array(commands, 0);
				error_message("Invalid command\n");
				return (NULL);
			}
		}
		commands[index] = strdup(list->value);
		move_pointer(&list);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}
