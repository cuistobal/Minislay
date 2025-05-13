/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 08:58:22 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	update_pwd_value(t_shel *minishell)
{

}

static void	handle_absolute_path(t_shel *minsihell, char *path)
{

}

static void	handle_relative_path(t_shel *minishell, char *path)
{

}

// Modify the PWD && OLDPWD variables
// If OLDPWD == CDPATH -> printf(PWD)
void	cd(t_shel *minishell, char *path)
{
	char	*current_directory;

	if (!minishell || !path)
		return ;
	current_directory = getcwd(current_directory, BUFFER_SIZE);

	//Using cd on the current working directory triggers a specific behaviour

	if (strcmp(current_directory, path) == 0)
	{
		printf("%s\n", current_directory);
		return ;
	}

	//

	if (is_absolute(path))
	{
		handle_absolute_path(minishell, path);
		return ;
	}
	else
	{
		handle_relative_path(minishell, path);
		return ;
	}
}
