/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:08:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/01 09:04:19 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shel *minishell, t_tokn *list, int count)
{
	int		index;
	char	**commands;

	index = 0;
	commands = (char **)calloc(count + 1, sizeof(char *));
	if (!commands)
		return (NULL);
	while (list)
	{
		if (index == 0)
		{
			if (!is_builtin(list->value) && !is_absolute(list->value))
			{
				if (!is_executable(list->value))
				{
					if (!retrieve_path(minishell, &list->value))
						return (NULL);
				}
			}
		}
		commands[index++] = list->value;
		move_pointer(&list);
	}
	commands[++index] = NULL;
	return (commands);
}
