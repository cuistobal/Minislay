/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 14:56:35 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
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
static bool	append_heredoc(char *expanded, int fd)
{
	if (expanded)
	{
		if (!write(fd, expanded, strlen(expanded)))
			return (false);
	}
	return (write(fd, "\n", 1));
}

static void setup_heredoc_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
static void restore_shell_signals(void)
{
    init_signals();
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
	//restore_shell_signals();
// 	if (g_signal_status == SIGINT)
// 	{
// 		if (line)
// 		{
// 			free(line);
// 			line = NULL;
// 		}
// 		append_exit_code(minishell, 130);
// 		g_signal_status = 0;
// 		return (NULL);
// 	}
// 	rl_on_new_line();
// 	return (line);
   // Si Ctrl+C, affiche ^C et retourne NULL
    if (!line && g_signal_status == SIGINT)
    {
        write(STDERR_FILENO, "^C\n", 3);
        append_exit_code(minishell, 130);
        return (NULL);
    }
    
    // Si Ctrl+D, affiche le warning
    if (!line)
	{
        return (error_message(SIG_HERE_DOC), error_message(limiter), \
		error_message("')\n"), NULL);
		append_exit_code(minishell, 0);
	}
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
	len = strlen(limiter) - 1;
	while (true)
	{
		line = get_user_input(minishell, limiter);
        if (!line)
        {
            close(redirections->type);
            free(limiter);
			limiter = NULL;
          //  if (g_signal_status == SIGINT)
                return (false);
            break;
        }
		if (*line && !strncmp(line, limiter, len) && (int)strlen(line) == len)
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
 */

 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:41:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 14:56:35 by chrleroy         ###   ########.fr       */
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

static bool	append_heredoc(char *expanded, int fd)
{
    if (expanded)
    {
        if (!write(fd, expanded, strlen(expanded)))
            return (false);
    }
    return (write(fd, "\n", 1));
}

static void setup_heredoc_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = SIG_IGN;  // Changed from SIG_DFL to SIG_IGN
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

static char *get_user_input(t_shell *minishell, char *limiter)
{
    char *line;
    struct termios term;
    struct termios original;

    tcgetattr(STDIN_FILENO, &original);
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
    setup_heredoc_signals();
    line = readline(HERE);
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    init_signals();

    // Handle Ctrl+C
    if (g_signal_status == SIGINT)
    {
        write(STDERR_FILENO, "^C\n", 3);
        g_signal_status = 0;
        append_exit_code(minishell, 130);
        return (NULL);
    }
    
    // Handle Ctrl+D (EOF)
    if (!line)
    {
        error_message(SIG_HERE_DOC);
        write(2, limiter, strlen(limiter) - 1);
        error_message("')\n");
        append_exit_code(minishell, 0);
        return (NULL);
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

    expanded = NULL;
    expansions = true;
    limiter = init_heredoc(redirections, &expansions);
    if (!limiter)
        return (false);
    len = strlen(limiter);
    while (true)
    {
        line = get_user_input(minishell, limiter);
        if (!line)
        {
            close(redirections->type);
			redirections->type = -2;
            free(limiter);
            return (false);
        }
        if (*line && !strncmp(line, limiter, len) && (int)strlen(line) == len)
            break ;
        expanded = expand_line(minishell, line, expansions);
        if (*line && !expanded && *line != '$')
        {
            free(line);
            free(limiter);
            close(redirections->type);
            return (false);
        }
        append_heredoc(expanded, redirections->type);
        free_user_input(&line, &expanded);
    }
    return (free(line), free(limiter), rewind_heredoc(redirections));
}