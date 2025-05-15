/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 17:49:38 by ynyamets         ###   ########.fr       */
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

int	get_minishelled(t_shell **minishell, char *input);
int	mini_loop(t_shell **minishell);
//int	minishell(char *input);
int	main(int argc, char **argv, char **envp);
//int	main(void);

//initialisation.c
bool    set_env(t_shell **minishell, char **envp);
bool	append_specials(t_shell **minishell);

#endif
