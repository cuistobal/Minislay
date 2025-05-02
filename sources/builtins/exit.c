/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:21:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/02 08:45:35 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	my_exit(t_shel *minishell)
{
//	if (minishell->expt)
//		free_tree(minishell->expt);
	if (minishell->expt)
		free(minishell->expt);	
	if (minishell->envp)
		free_env_list(minishell->envp);
	if (minishell->command)
		free_env_list(minishell->command);	
	exit(0);
}
