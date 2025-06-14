/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:39:16 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 22:44:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	start_process_helper(struct termios *old_term, bool *signal)
{
	*signal = false;
	tcgetattr(STDIN_FILENO, old_term);
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
	start_process_helper(&old_term, &signal);
	while (1)
	{
		handle_terminal_settings(&term);
		user_input = readline(terminal_name);
		if (!user_input)
			return (handle_eof(*minishell, &old_term));
		if (*user_input && process_input(minishell, user_input, &term, \
					&retcode))
			break ;
		rl_replace_line("", 0);
	}
	return (end_process(&old_term, retcode));
}
