/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:21:59 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*expand_line(t_shell *minishell, char *line, bool expansions)
{
	int		index;
	char	*expanded;
	char	*value;

	if (!line)
		return (NULL);
	if (!expansions)
		return (ft_strdup(line));
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
static bool	append_heredoc(char *expanded, int fd)
{
	if (expanded)
	{
		if (!write(fd, expanded, ft_strlen(expanded)))
			return (false);
	}
	return (write(fd, "\n", 1));
}

static char	*get_user_input(void)
{
	char	*line;

	line = readline(HERE);
	rl_on_new_line();
	return (line);
}

static void	free_user_input(char **line, char **expanded)
{
	free(*line);
	line = NULL;
	free(*expanded);
	*expanded = NULL;
}

//This utility creates a temporary file and fills it with the user's input. If
//the limiter is an unquoted token, lines get expanded.
bool	handle_here_doc(t_shell *minishell, t_tokn *redirections)
{
	int		len;
	char	*line;
	char	*limiter;
	char	*expanded;
	bool	expansions;

	expanded = NULL;
	expansions = true;
	limiter = init_heredoc(redirections, &expansions);
	if (!limiter)
		return (false);
	len = ft_strlen(limiter) - 1;
	while (true)
	{
		line = get_user_input();
		if (*line && !ft_strncmp(line, limiter, len) && ft_strlen(line) == len)
			break ;
		expanded = expand_line(minishell, line, expansions);
		if (*line && !expanded && *line != '$')
			return (free(line), free(limiter), close(redirections->type), \
					false);
		append_heredoc(expanded, redirections->type);
		free_user_input(&line, &expanded);
	}
	return (free(line), free(limiter), rewind_heredoc(redirections));
}
