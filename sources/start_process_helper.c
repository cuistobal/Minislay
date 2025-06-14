/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:44:16 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 22:28:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
** Configures terminal settings for readline and heredoc
** - Enables canonical mode (ICANON) for line-by-line input
** - Enables echo for user input visibility
** - Disables control character echoing (ECHOCTL)
*/
void	handle_terminal_settings(struct termios *term)
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
int	handle_eof(t_shell *minishell, struct termios *old_term)
{
	int	code;

	code = get_last_exit_code(minishell);
	write(STDOUT_FILENO, "exit\n", 5);
	tcsetattr(STDIN_FILENO, TCSANOW, old_term);
	free_minishell(minishell);
	exit(code);
	return (code);
}

/*
** Performs cleanup after command execution:
** - Waits for all child processes to finish
** - Frees user input memory
** - Updates shell exit code if needed
*/
void	wait_processes_and_clean(char *user_input)
{
	while (wait(NULL) > 0)
		continue ;
	free(user_input);
}

/*
** Processes valid user input:
** - Adds command to history
** - Executes command through minishell pipeline
** - Handles terminal settings restoration
** - Manages process cleanup
*/
bool	process_input(t_shell **minishell, char *user_input, \
		struct termios *term, int *retcode)
{
	add_history(user_input);
	if (input_is_space(user_input))
		return (false);
	*retcode = get_minishelled(minishell, user_input);
	handle_terminal_settings(term);
	wait_processes_and_clean(user_input);
	if (is_state_active(*retcode, EXIT_MASK))
		return (unset_state(retcode, EXIT_MASK), true);
	return (false);
}

int	end_process(struct termios *old_term, int retcode)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_term);
	rl_clear_history();
	return (retcode);
}
