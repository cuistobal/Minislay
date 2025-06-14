/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:49:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 18:14:05 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	handle_sigint_in_here_doc(t_shell *minishell)
{
	write(STDERR_FILENO, "^C\n", 3);
	g_signal_status = 0;
	append_exit_code(minishell, 130);
	init_signals();
	rl_on_new_line();
	rl_replace_line("", 0);
}

//
void	handle_sigquit_in_here_doc(t_shell *minishell, char *limiter)
{
	error_message(SIG_HERE_DOC);
	write(2, limiter, strlen(limiter) - 1);
	error_message("')");
	append_exit_code(minishell, 0);
	init_signals();
	rl_on_new_line();
	rl_replace_line("", 0);
}

//
void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
