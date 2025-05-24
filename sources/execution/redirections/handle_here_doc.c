/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/24 15:06:19 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*expand_line(t_shell *minishell, char *line, bool expansions)
{
	int		index;
	char	*temp;
	char	*value;
	char	*expanded;

	temp = NULL;
	value = NULL;
	expanded = NULL;
	if (!line)
		return (NULL);
	if (!expansions)
		expanded = strdup(line);
	else
	{
		index = 0;
		while (line[index])
		{
			if (!get_expanded(minishell, line, &value, &index))
				return (NULL);
			temp = expanded;
			if (!get_merged(&expanded, &temp, &value))
				return (NULL);
		}
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
			return false;
	}
	return (write(fd, "\n", 1));
}

static char	*init_heredoc(t_tokn *redirections, bool *expansions)
{
	int		fd;
	char	*limiter;

	limiter = NULL;
	if (!redirections)
		return (NULL);
//	limiter = limiter_handler(redirections->next->value, expansions);
	limiter = limiter_handler(redirections->value, expansions);
	if (!limiter)
		return (NULL);
	fd = open(redirections->value, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (fd <  0)
		return (free(limiter), NULL);
	redirections->type = fd;
	return (limiter);
}

//This utility creates a temporary file and fills it with the user's input. If
//the limiter is an unquoted token, lines get expanded.
bool	handle_here_doc(t_shell *minishell, t_tokn *redirections)
{
	char	*line;
	char	*limiter;
	char	*expanded;
	bool	expansions;

	expanded = NULL;
	expansions = true;
	limiter = init_heredoc(redirections, &expansions);
	if (!limiter)
		return (false);
	line = readline(HERE);
	rl_on_new_line();
	while (line)
	{
		if (!strncmp(line, limiter, strlen(line)) && strlen(line) > 0)
			break ;
		expanded = expand_line(minishell, line, expansions);
		if (!expanded)
			return (free(line), close(redirections->type), false);
		append_heredoc(expanded, redirections->type);
		free(expanded);
		free(line);
		line = readline(HERE);
		rl_on_new_line();
	}
	return (free(line), true);//close(redirections->type), true);
}
