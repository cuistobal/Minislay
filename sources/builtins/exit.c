/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:21:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/02 10:37:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	my_exit(t_shel *minishell)
{
	int	index;

	index = 0;
	if (minishell->expt)
		free_avlt(minishell->expt);
	if (minishell->envp)
		free_env_list(minishell->envp);
	if (minishell->command)
		free_env_list(minishell->command);	
	while (minishell->special[index])
		free(minishell->special[index++]);
	free(minishell);
	exit(0);
}
