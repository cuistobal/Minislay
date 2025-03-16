#include "minislay.h"
//#include "globing.h"

static bool	insert_globing_result(t_tokn **list, t_tokn *head, char *filename)
{
	t_tokn	*new;
	char	*value;

	value = strdup(filename);
	if (value)
	{
		if (*list == head)
		{
			free((*list)->value);
			(*list)->value = value;
		}
		else
		{
			new = create_token_node(value, WORD);
			if (new)
			{
				(*list)->next = new;
				*list = new;
				return (true);
			}
			free (value);
		}
	}
	return (false);	
}

//static char	**globing_loop(char **patterns, DIR *stream, int *size)
static bool	globing_loop(t_tokn **list, char **patterns, DIR *stream)
{
	t_tokn			*next;
	t_tokn			*head;
	struct dirent	*current;

	current = NULL;
	head = *list;
	next = head->next;
	if (patterns && stream)
	{
		current = readdir(stream);
		while (current)
		{
			if (match_pattern(patterns, current->d_name))
			{
				if (!insert_globing_result(list, head, current->d_name))	
					return ((*list)->next = next ,false);
			}
			current = readdir(stream);
		}
		(*list)->next = next;
		*list = next;
	}
	return (true);		//To be modified
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
//char	**globing(const char *globing, const char *path, int *count)
bool	globing(t_tokn **list, const char *path) 
{
	char	**patterns;
	DIR		*dir_stream;

	patterns = NULL;
	dir_stream = NULL;
	if (*list)
	{
		if (open_directory(path, &dir_stream))
		{
			patterns = identify_globing_patterns((*list)->value);
			if (patterns)
			{
				if (globing_loop(list ,patterns, dir_stream))
					return (closedir(dir_stream), true);
			}
			closedir(dir_stream);
		}
	}
	return (false);
}
