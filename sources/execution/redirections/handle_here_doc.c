#include "minislay.h"
/*
static bool	insert_expansion()
{

}
*/
//This function expands the line. 
static bool	expand_line(t_shel *minishell,	char **line)
{
	int		index;
	char	*temp;
	char	*value;
	char	*merged;

	temp = NULL;
	value = NULL;
	merged = NULL;
	if (*line)
	{
		index = 0;
		while (*line[index])
		{
			if (!get_expanded(minishell, *line, &value, &index))
				return (false);	
			if (strncmp(value, *line, strlen(value)) == 0)
				index++;
			else
			{
				temp = merged;
				if (!get_merged(&merged, &temp, &value))
					return (false);
				printf("%s\n", merged);
			}
		}
	//	*line = merged;

	//		printf("%d	%c\n", *line[index], *line[index]);
	//		if (*line[index] == '\0' || *line[index] == '\n')
	//			break ;
	//	}
//		free(*line);
//		*line = merged;
		printf("after expansion		->	%s vs %s\n", *line, merged);
		return (*line[index] == '\0');
	}
	return (*line);
}

static char	*limiter_handler(char *limiter, bool *expansions)
{
	int		index;
	char	*merged;

	merged = NULL;
	if (limiter)
	{
		index = 0;
		if (is_quote(*limiter))
		{
			*expansions = false;
			merged = strdup(limiter + 1);
			if (merged)
			{
				while (merged[index])
				{
					if (merged[index] == '"')
					{
						merged[index] = '\n';
						return (merged);
					}
					index++;
				}
			}
			return (NULL);
		}
		merged = ft_strjoin(limiter, "\n");
		free(limiter);
	}
	return (merged);
}

//This utility creates a temporary file and fills it with the user's input. If
//the limiter is an unquoted token, lines get expanded.
bool	handle_here_doc(t_shel *minishell, t_tokn **redirections)
{
	int		fd;
	char	*line;
	char	*limiter;
	bool	expansions;

	expansions = true;
	limiter = limiter_handler((*redirections)->value, &expansions);
	if (limiter)
	{
		fd = open("heredoc", O_APPEND | O_CREAT | O_RDWR, 0644);
		if (fd >= 0)
		{
			(*redirections)->type = fd;
			line = readline(">");
			rl_on_new_line();
			while (line) 
			{
				if (strncmp(line, limiter, strlen(line)) == 0)
					return (free(line), close(fd), true);
				if (expansions)
				{
					if (!expand_line(minishell, &line))
						return (printf("EXPANSION ERROR\n"), close(fd), false);
				}
				if (write(fd, line, strlen(line)))
				{
					if (!write(fd, "\n", 1))
						return (free(line), close(fd), printf("Can't write into %d\n", fd), false);	
				}
				free(line);
				line = readline(">");
				rl_on_new_line();
			}	
		}
	}
	return (printf("Unable to open heredoc with %s\n", (*redirections)->value), false);
}
