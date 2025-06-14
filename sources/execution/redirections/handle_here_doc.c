/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 16:56:39 by chrleroy         ###   ########.fr       */
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
		return (strdup(line));
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
		if (!write(fd, expanded, strlen(expanded)))
			return (false);
	}
	return (write(fd, "\n", 1));
}

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
		//return (write(STDERR_FILENO, "^C\n", 3), g_signal_status = 0, \
				append_exit_code(minishell, 130), init_signals(), NULL);
	if (!line)
	{
		return (handle_sigquit_in_here_doc(minishell, limiter), NULL);
	//	error_message(SIG_HERE_DOC);
	//	return (write(2, limiter, strlen(limiter) - 1), error_message("')\n"), \
				append_exit_code(minishell, 0), init_signals(), NULL);
	}
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
	char	*line;
	char	*limiter;
	char	*expanded;
	bool	expansions;

	expansions = true;
	if (!init_heredoc(redirections, &expansions, &limiter, &len))
		return (false);
	while (true)
	{
		line = get_user_input(minishell, limiter);
		if (!line)
			return (close(redirections->type), redirections->type = -2, \
					free(limiter), false);
		if (*line && (int)strlen(line) == len && !strcmp(line, limiter))
			break ;
		expanded = expand_line(minishell, line, expansions);
		if (*line && !expanded && *line != '$')
			return (free(line), free(limiter), close(redirections->type), \
					false);
		append_heredoc(expanded, redirections->type);
		free_user_input(&line, &expanded);
	}
	return (free(line), free(limiter), init_signals(), \
	rewind_heredoc(redirections));
}
