/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/04 08:37:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISLAY_H
# define MINISLAY_H

# include "standard_headers.h"
# include "global_variables.h"
# include "structures.h"
# include "utilities.h"
# include "../minitester/utils/minislay_test.h"
# include "parsing.h"

int	minishell(char *input);
int	main(int argc, char **argv, char **envp);
//int	main(void);

//initialisation.c
bool    set_env(t_shel **minishell, char **envp);

#endif
