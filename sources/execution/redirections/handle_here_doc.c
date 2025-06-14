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

static char	*expand_line(t_shell *minishell, char *line, bool expansions)
{
	int		index;
	char	*expanded;
	char	*value;

	if (!line)
		return (NULL);
	if (!expansions)
		return (ft_strdup(line));
	index = 0;
	value = NULL;
	expanded = NULL;
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

static bool	append_heredoc(char *expanded, int fd)
{
	if (expanded)
	{
		if (!write(fd, expanded, ft_strlen(expanded)))
			return (false);
	}
	return (write(fd, "\n", 1));
}

//
static char	*get_user_input(t_shell *minishell, char *limiter)
{
	char			*line;
	struct termios	term;
	struct termios	original;

	tcgetattr(STDIN_FILENO, &original);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	setup_heredoc_signals();
	line = readline(HERE);
	tcsetattr(STDIN_FILENO, TCSANOW, &original);
	if (g_signal_status == SIGINT)
		return (handle_sigint_in_here_doc(minishell), NULL);
	if (g_signal_status == SIGQUIT)
		return (handle_sigquit_in_here_doc(minishell, limiter), NULL);
	return (line);
}

static void	free_user_input(char **line, char **expanded)
{
	free(*line);
	*line = NULL;
	free(*expanded);
	*expanded = NULL;
}

bool	handle_here_doc(t_shell *minishell, t_tokn *redirections)
{
	int		len;
	char	*lim;
	char	*line;
	char	*expanded;
	bool	expansions;

	if (!init_heredoc(redirections, &expansions, &lim, &len))
		return (false);
	while (true)
	{
		line = get_user_input(minishell, lim);
		if (!line)
			return (close(redirections->type), redirections->type = -2, \
					free(lim), false);
		if (*line && ft_strlen(line) == (len - 1) && !ft_strncmp(line, lim, len - 1))
			break ;
		expanded = expand_line(minishell, line, expansions);
		if (*line && !expanded && *line != '$')
			return (free(line), free(lim), \
					close(redirections->type), false);
		append_heredoc(expanded, redirections->type);
		free_user_input(&line, &expanded);
	}
	return (free(line), free(lim), init_signals(), \
			rewind_heredoc(redirections));
}
