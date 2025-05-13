/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:47:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Modify the PWD && OLDPWD variables
// If OLDPWD == CDPATH -> printf(PWD)
void	cd(t_shel *minishell, char *path)
{
	char	*value;
	char	*current_directory;

	memset(current_directory, 0, BUFFER_SIZE);

	if (!minishell || !path)
		return ;

	current_directory = getcwd(current_directory, BUFFER_SIZE);

	//Using cd on the current working directory triggers a specific behaviour

	if (strcmp(current_directory, path) == 0)
		printf("%s\n", current_directory);

	//

	else 
	{
		if (chdir(path) != 0)
			printf("bash: cd: %s: No such file or directory\n", path);
		else
		{
			update_key_value(minishell, "OLDPWD", current_directory);
			memset(current_directory, 0, BUFFER_SIZE);
			current_directory = getcwd(current_directory, BUFFER_SIZE);
			update_key_value(minishell, "PWD", current_directory);
		}
	}
	return ;
}
