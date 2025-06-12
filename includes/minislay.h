/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:55:16 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISLAY_H
# define MINISLAY_H

# include "standard_headers.h"
# include "global_variables.h"
# include "expansions.h"
# include "structures.h"
# include "errors.h"
# include "utilities/utilities.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include "signals.h"
# include "utilities/libft.h"

//minnishell.c
int		get_minishelled(t_shell **minishell, char *input);
int		start_process(t_shell **minishell, char *terminal_name);
int		main(int argc, char **argv, char **envp);

//initialisation.c
bool	insert_env_in_avlt(t_shell *minishell);
void	build_rl_prompt(char *rl_prompt, char *tname);
t_env	*append_specials(void);
t_env	*create_env_node(char *line);

bool	build_env(t_shell **minishell, char **envp);
bool	set_env(t_shell *minishell, char **envp);

//start_process_helper.c
void	handle_terminal_settings(struct termios *term);
int		handle_eof(t_shell *minishell, struct termios *old_term);
void	wait_processes_and_clean(t_shell **minishell, char *user_input, \
		int retcode);
bool	process_input(t_shell **minishell, char *user_input, \
		struct termios *term, int *retcode);
int		end_process(struct termios *old_term, int retcode);

#endif
