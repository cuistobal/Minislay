#include "minislay.h"

//This function expands the line. 
static bool	expand_line(t_shel *minishell,	char **line)
{
	int		index;
	char	*value;

	value = NULL;
	if (*line)
	{
		printf("before expansion	->	%s\n", *line);
		index = 0;
		while (*line[index])
		{
			if (*line[index] == '$')
				get_expanded(minishell, line, &value, &index);
			index++;
		}
		printf("after expansion	->	%s\n", *line);
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
		printf("%s	->	%ld\n", limiter, strlen(limiter));
	fd = open("heredoc", O_APPEND | O_CREAT | O_RDWR, 0644);
	if (fd >= 0)
	{
		(*redirections)->type = fd;
		line = readline(">");
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
		}
	
	}
	}
	return (printf("Unable to open heredoc with %s\n", (*redirections)->value), false);
}
