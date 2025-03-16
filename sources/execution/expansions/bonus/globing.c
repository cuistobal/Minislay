#include "minislay.h"
//#include "globing.h"

//
static char **append_expanded(char **expanded, int *size, char *filename)
{
	(*size)++;
	expanded = (char **)realloc(expanded, sizeof(char *) * *size + 1);
	if (expanded)
	{
		expanded[*size - 1] = strdup(filename);
		if (!expanded[*size - 1])
		{
			free_array(expanded, *size);
			//memalloc failed
			return (NULL);
		}
		expanded[*size] = NULL;
		return (expanded);
	}
	free_array(expanded, *size);
	return (expanded);
}

//
static char	**globing_loop(char **patterns, DIR *stream, int *size)
{
	struct dirent	*current;
	char			**expanded;

	current = NULL;
	expanded = NULL;
	if (patterns && stream)
	{
		current = readdir(stream);
		while (current)
		{
			if (match_pattern(patterns, current->d_name))
			{
				if (current->d_type == DT_REG)
				{
					expanded = append_expanded(expanded, size, current->d_name);
					if (!expanded)
						//memalloc failed
						return (false);	
				}
			}
			current = readdir(stream);
		}
	}
	return (expanded);
}

//
static bool	open_directory(const char *dir_path, DIR **dir_stream)
{
	if (!*dir_stream)
	{
		if (dir_path)
			*dir_stream = opendir(dir_path);
		return (*dir_stream);
	}
	return (false);
}

//
char	**globing(const char *globing, const char *path, int *count)
{
	int		pindex;
	char	**patterns;
	char	**expanded;
	DIR		*dir_stream;

	pindex = 1;
	patterns = NULL;
	dir_stream = NULL;
	if (globing && path)
	{
		if (open_directory(path, &dir_stream))
		{
			patterns = identify_globing_patterns(globing, &pindex);
			if (patterns)
			{
				expanded = globing_loop(patterns, dir_stream, count);
				if (expanded)
				{
					free_array(patterns, pindex);
					closedir(dir_stream);
					return (expanded);
				}
				free_array(patterns, pindex);
			}
			closedir(dir_stream);
		}
		return (NULL); //allocation error
	}
	return (NULL); //invalid globing variable
}
