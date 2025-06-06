/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:08:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/07 11:05:52 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*get_token_copy(char *source)
{
	if (!source)
		return (strdup(""));
	else
		return (strdup(source));

}

//UNUSED RN
static bool	handle_command_argument(t_shell *m, char **cpy, int i)
{
	if (index > 0)
		return (true);
	if (is_builtin(*cpy) || is_absolute(*cpy) || is_executable(*cpy))
		return (true);
	if (retrieve_path(m, cpy))
		return (true);
	free(*cpy);
	return (error_message("Invalid command\n"));
}

//Utility to create the char **tab required for execution.
char	**get_command_and_arguments(t_shell *minishell, t_tokn *list)
{
	int		count;
	int		index;
    char    *copy;
	char	**commands;

	index = 0;
	if (!list)
		return (NULL);
	commands = (char **)calloc(TAB_SIZE, sizeof(char *));
	if (!commands)
		return (NULL);
	while (list)
	{
		copy = get_token_copy(list->value);
		if (index == 0 && !is_builtin(copy) && !is_absolute(copy))
		{
			if (!is_executable(copy) && !retrieve_path(minishell, &copy))
				return (free(copy), free(commands), error_message("Invalid command\n"), NULL);
		}
		commands[index] = copy;
		move_pointer(&list);
		index++;
	}
	commands[index] = NULL;
	//commands = (char **)reallc(commands, sizeof(char *) * (index + 1));
	return (commands);
}
