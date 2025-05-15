/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 10:15:34 by chrleroy         ###   ########.fr       */
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
#include "builtins.h"

//minnishell.c
int		get_minishelled(t_shel **minishell, char *input);
int		mini_loop(t_shel *minishell, char *terminal_name);
int		main(int argc, char **argv, char **envp);

//initialisation.c
bool	insert_env_in_avlt(t_shel *minishell);
void	build_rl_prompt(char *rl_prompt, char *tname);
//bool 	build_env(t_shel *minishell, char **envp);
//bool 	build_env(t_shel **minishell, char **envp);
bool	append_specials(t_shel **minishell);
t_env	*create_env_node(t_env **prev, char *value);

//bool    set_env(t_shel *minishell, char **envp);

#endif
