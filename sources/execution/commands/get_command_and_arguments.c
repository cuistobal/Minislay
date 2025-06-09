/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_and_arguments.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:08:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 09:16:05 by cuistobal        ###   ########.fr       */
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

//
static bool handle_command(t_shell *minishell, char **copy, int index)
{
	if (index == 0 && !is_builtin(*copy) && !is_absolute(*copy))
	{
		if (!is_executable(*copy) && !retrieve_path(minishell, copy))
            return (error_message("Invalid command\n"));
    }
    return (true);
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
        if (!handle_command(minishell, &copy, index))
            return (free(copy), free(commands), NULL);
		commands[index] = copy;
		move_pointer(&list);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}
