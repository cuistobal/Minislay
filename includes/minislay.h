/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 12:28:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISLAY_H
# define MINISLAY_H

# include "standard_headers.h"
# include "global_variables.h"
# include "expansions.h"
# include "structures.h"
# include "containers.h"
# include "errors.h"
# include "utilities/utilities.h"
# include "../minitester/utils/minislay_test.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include "signals.h"

//minnishell.c
int		get_minishelled(t_shell **minishell, char *input);
int		start_process(t_shell **minishell, char *terminal_name);
int		main(int argc, char **argv, char **envp);

//initialisation.c
bool	insert_env_in_avlt(t_shell *minishell);
void	build_rl_prompt(char *rl_prompt, char *tname);
t_env	*append_specials(void);
t_env	*create_env_node(char *line);

bool    set_env(t_shell *minishell, char **envp);

#endif
