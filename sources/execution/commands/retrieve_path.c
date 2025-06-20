/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:50:45 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 18:50:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Lastly, we try to access the command binary throughthe different paths we 
//found.
static bool	test_path(char **command, char *path)
{
	char	*temp;
	char	*merged;

	temp = NULL;
	merged = NULL;
	if (!path)
		return (false);
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (false);
	merged = ft_strjoin(temp, *command);
	if (!merged)
		return (false);
	free(temp);
	if (access(merged, F_OK | X_OK) != 0)
		return (free(merged), false);
	return (free(*command), *command = merged, true);
}

//We use this function to loop trough the PATH contained in env.
static bool	try_path(char **command, char *path)
{
	char	*copy;
	char	*try_path;

	copy = NULL;
	try_path = NULL;
	if (!path)
		return (false);
	copy = ft_strdup(path);
	try_path = copy;
	while (*try_path)
	{	
		if (test_path(command, ft_strtok_r(try_path, ":", &try_path)))
		{
			free(copy);
			return (true);
		}
	}
	free(copy);
	return (false);
}

//We use this function to retrieve the PATH env variable.
bool	retrieve_path(t_shell *minishell, char **command)
{
	char	*path;

	path = NULL;
	if (!minishell || !*command)
		return (false);
	if (find_key_in_env(minishell->envp, &path, PATH))
		return (try_path(command, path));
	return (false);
}
