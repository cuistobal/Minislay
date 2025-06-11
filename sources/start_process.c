/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:39:16 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 18:56:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
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
		}
		if (*user_input && process_input(minishell, user_input, &term, \
					&retcode))
			break ;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return (end_process(&old_term, retcode));
}
