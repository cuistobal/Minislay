/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 20:56:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Modify the PWD && OLDPWD variables
// If OLDPWD == CDPATH -> printf(PWD)
int	cd(t_shel *minishell, char **arguments)
{
	char	*path;
//	char	*value;
	char	current_directory[BUFFER_SIZE];

//	memset(current_directory, 0, BUFFER_SIZE);

	if (!minishell)
		return (-1);

	path = *arguments;
	getcwd(current_directory, BUFFER_SIZE);

	if (!path)
	{	
		printf("%s\n", current_directory);
		return (-1);
	}

	//Using cd on the current working directory triggers a specific behaviour

	if (strcmp(current_directory, path) == 0)
	{
		printf("%s\n", current_directory);
		return (-1);
	}
	//

	else 
	{
		if (chdir(path) != 0)
			printf("bash: cd: %s: No such file or directory\n", path);
		else
		{
			update_key_value(minishell, "OLDPWD", current_directory);
			memset(current_directory, 0, BUFFER_SIZE);
			getcwd(current_directory, BUFFER_SIZE);
			update_key_value(minishell, "PWD", current_directory);
		}
	}
	return (0);
}
