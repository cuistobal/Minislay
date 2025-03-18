#include "minislay.h"

static bool	try_path(char **command, char *path, int *index)
{
	int		start;
	char	*copy;
	char	*merged;

	copy = NULL;
	merged = NULL;
	start = *index;
	if (path)
	{
		//Iterate through the PATH's variables

		while (path[*index])
		{
			if (isspace(path[*index]))
				break ;
			(*index)++;
		}

		//Retrieve a PATH and merge it with the current command
		copy = strndup(path + start, *index);
		if (copy)
		{
			merged = ft_strjoin(copy, *command);
			if (merged)
			{
				if (access(merged, X_OK))
				{
					*command = merged;
					return (true);
				}
			}
		}
	}
	return (false);
}

//We use this function to retrieve the path to the command's binary.
bool	retrieve_path(t_shel *minishell, char **command)
{
	char	*temp;
	char	*path;
	int		index;

	index = 0;
	temp = NULL;
	path = NULL;
	if (minishell && *command)
	{
		if (find_key(minishell, &path, PATH))
		{
			while (!try_path(command, path, &index))
				index++;

		}
	}
}
