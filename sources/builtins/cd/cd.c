/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:27:05 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Modify the PWD && OLDPWD variables
// If OLDPWD == CDPATH -> printf(PWD)
void	cd(t_shel *minishell, char *path)
{
	char	*value;
	char	*current_directory;

	if (!minishell || !path)
		return ;
	current_directory = getcwd(current_directory, BUFFER_SIZE);

	//Using cd on the current working directory triggers a specific behaviour

	if (strcmp(current_directory, path) == 0)
		printf("%s\n", current_directory);

	else 
	{
		if (chdir(path) != 0)
			error_message("bash: cd: dqwqwdqwdqdw: No such file or directory");
		else
		{
			find_key(minishell, &value, PWD);
			
			update_key(minishell, PWD, );
			update_key(minishell, PWD, );
		}
	}
	return ;
}
