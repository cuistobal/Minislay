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
	if (!access(merged, F_OK | X_OK) == 0)
		return (free(merged), false);
	*command = merged;
	return (true);
}

//We use this function to loop trough the PATH contained in env.
static bool	try_path(char **command, char *path)
{
	char	*copy;

	copy = NULL;
	if (!path)
		return (false);
	copy = strdup(strtok_r(path, ":", &path));
	while (copy)
	{
		if (test_path(command, copy))
			return (free(copy), true);
		free(copy);
		copy = strtok_r(path, ":", &path);
		if (copy)
			copy = strdup(copy);
	}
	//Error message -> No path
	return (false);
}

//We use this function to retrieve the PATH env variable.
bool	retrieve_path(t_shel *minishell, char **command)
{
	char	*path;

	path = NULL;
	if (!minishell || !*command)
		return (false);
	if (find_key(minishell, &path, PATH))
		return (try_path(command, path));
	return (false);
}
