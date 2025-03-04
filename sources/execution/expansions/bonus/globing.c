//#include "minislay.h"
#include "globing.h"

//
static char **append_expanded(char **expanded, int *size, char *filename)
{
	char	*dup;
	char	**temp;

	(*size)++;
	temp = expanded;
	expanded = (char **)realloc(expanded, sizeof(char *) * *size);
	if (expanded)
	{
		expanded[*size - 2] = strdup(filename);
		if (!expanded[*size - 2])
		{
			free_array(expanded, *size);
			//memalloc failed
			return (NULL);
		}
		expanded[*size - 1] = NULL;
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
				expanded = append_expanded(expanded, size, current->d_name);
				if (!expanded)
					//memalloc failed
					return (false);
			}
			current = readdir(stream);
		}
		return (expanded);
	}
	return (NULL);	
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
