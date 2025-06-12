/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:39:16 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:59:41 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	redisplay(bool *signal)
{
	*signal = false;
	rl_on_new_line();
}

static void	handle_signal_in_process_loop(char **user_input, bool *signal)
{
	g_signal_status = 0;
	free(user_input);
	*user_input = NULL;
	*signal = true;
}

//
int	start_process(t_shell **minishell, char *terminal_name)
{
	bool			signal;
	int				retcode;
	char			*user_input;
	struct termios	term;
	struct termios	old_term;

	init_signals();
	signal = false;
	tcgetattr(STDIN_FILENO, &old_term);
	while (1)
	{
		handle_terminal_settings(&term);
		user_input = readline(terminal_name);
		if (!user_input)
			return (handle_eof(*minishell, &old_term));
		if (g_signal_status == SIGQUIT)
			handle_signal_in_process_loop(&user_input, &signal);
		if (*user_input && process_input(minishell, user_input, &term, \
					&retcode))
			break ;
		if (signal)
			redisplay(&signal);
		rl_replace_line("", 0);
	}
	return (end_process(*minishell, &old_term, retcode));
}
