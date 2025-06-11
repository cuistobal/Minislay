/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 11:12:44 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool rewind_heredoc(t_tokn *redirections)
{
    if (access(redirections->value, F_OK) != 0)
        return (false);
    close(redirections->type);
    redirections->type = open(redirections->value, O_RDONLY);
    return (redirections->type != -1);
}

static char	*expand_line(t_shell *minishell, char *line, bool expansions)
{
    int		index;
    char	*expanded;
    char	*value;

    if (!line)
        return (NULL);
    if (!expansions)
        return (strdup(line));

    expanded = NULL;
    value = NULL;
    index = 0;
    while (line[index])
    {
        if (!get_expanded(minishell, line, &value, &index))
            return (free(expanded), NULL);

        expanded = get_merged(&expanded, &expanded, &value);
        if (!expanded)
            return (free(value), NULL);
    }
    return (expanded);
}

//
static char	*limiter_handler(char *limiter, bool *expansions)
{
	int		index;
	char	*merged;

	merged = NULL;
	if (limiter)
	{
		index = 0;
		if (!is_quote(*limiter))
			return (ft_strjoin(limiter, "\n"));
		*expansions = false;
		merged = strdup(limiter + 1);
		if (merged)
		{
			while (merged[index])
			{
				if (merged[index] == '"')
					break ;
				index++;
			}
			merged[index] = '\n';
		}
	}
	return (merged);
}

//
static bool	append_heredoc(char *expanded, int fd)
{
	if (expanded)
	{
		if (!write(fd, expanded, strlen(expanded)))
			return (false);
	}
	return (write(fd, "\n", 1));
}

//
static char	*init_heredoc(t_tokn *redirections, bool *expansions)
{
	int		fd;
	char	*limiter;
	char	*heredocname;	

	limiter = NULL;
	if (!redirections)
		return (NULL);
	limiter = limiter_handler(redirections->value, expansions);
	if (!limiter)
		return (NULL);
	heredocname = ft_strjoin(HEREDOC_PREFIX, redirections->value);
	if (!heredocname)
		return (free(limiter), NULL);
	free(redirections->value);
	redirections->value = heredocname;
	fd = open(heredocname, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd <  0)
		return (free(limiter), NULL);
	redirections->type = fd;
	return (limiter);
}

//This utility creates a temporary file and fills it with the user's input. If
//the limiter is an unquoted token, lines get expanded.
bool	handle_here_doc(t_shell *minishell, t_tokn *redirections)
{
    int     len;
	char	*line;
	char	*limiter;
	char	*expanded;
	bool	expansions;

	expanded = NULL;
	expansions = true;
	limiter = init_heredoc(redirections, &expansions);
	if (!limiter)
		return (false);
    len = strlen(limiter) - 1;
	while (true)
	{
		line = readline(HERE);
		rl_on_new_line();
		if (*line && !strncmp(line, limiter, len) && strlen(line) == len)
            break ;
		expanded = expand_line(minishell, line, expansions);
		if (*line && !expanded && *line != '$')
			return (free(line), free(limiter), close(redirections->type), false);
		append_heredoc(expanded, redirections->type);
		free(expanded);
		free(line);
	}
	return (free(line), free(limiter), rewind_heredoc(redirections));
}
