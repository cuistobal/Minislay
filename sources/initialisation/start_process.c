/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:39:16 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 17:35:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
** Configures terminal settings for readline and heredoc
** - Enables canonical mode (ICANON) for line-by-line input
** - Enables echo for user input visibility
** - Disables control character echoing (ECHOCTL)
*/
static void	handle_terminal_settings(struct termios *term)
{
    tcgetattr(STDIN_FILENO, term);
    term->c_lflag |= (ECHO | ICANON);
    term->c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, term);
}

/*
** Handles EOF (Ctrl+D) condition:
** - Displays exit message
** - Restores original terminal settings
** - Exits the program cleanly
*/
static int	handle_eof(t_shell *minishell, struct termios *old_term)
{
    write(STDOUT_FILENO, "exit\n", 5);
    tcsetattr(STDIN_FILENO, TCSANOW, old_term);
	free_minishell(minishell);
    exit(0);
    return (EXIT_CODE);
}

/*
** Performs cleanup after command execution:
** - Waits for all child processes to finish
** - Frees user input memory
** - Updates shell exit code if needed
*/
static void	wait_processes_and_clean(t_shell **minishell, char *user_input,
        int retcode)
{
    while (wait(NULL) > 0)
        continue ;
    free(user_input);
    if (retcode != EXIT_CODE)
        append_exit_code(*minishell, retcode, false);
}

/*
** Processes valid user input:
** - Adds command to history
** - Executes command through minishell pipeline
** - Handles terminal settings restoration
** - Manages process cleanup
*/
static int	process_input(t_shell **minishell, char *user_input,
        struct termios *term)
{
    int	retcode;

    add_history(user_input);
    retcode = get_minishelled(minishell, user_input);
    handle_terminal_settings(term);
    wait_processes_and_clean(minishell, user_input, retcode);
    return (retcode);
}

/*
** Main shell loop:
** - Initializes signal handlers and terminal settings
** - Reads and processes user input
** - Manages command execution flow
** - Handles terminal cleanup and program exit
*/
int	start_process(t_shell **minishell, char *terminal_name)
{
    int				retcode;
    char			*user_input;
    struct termios	term;
    struct termios	old_term;

    init_signals();
    tcgetattr(STDIN_FILENO, &old_term);
    while (1)
    {
        handle_terminal_settings(&term);
        user_input = readline(terminal_name);
        if (!user_input)
            return (handle_eof(*minishell, &old_term));
        if (g_signal_status == SIGQUIT)
        {
            g_signal_status = 0;
            free(user_input);
            continue ;
        }
        if (*user_input && (retcode = process_input(minishell, user_input,
                    &term)) == EXIT_CODE)
            break ;
        rl_on_new_line();
        rl_replace_line("", 0);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    rl_clear_history();
    return (retcode);
}