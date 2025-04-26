/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:17:46 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:23:00 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	cleanup(t_shel *minishell, int exit_code)
{
	if (minishell)
	{
		if (minishell->expt)
		{
			free(minishell->expt);	
			minishell->expt = NULL;	
		}
		if (minishell->envp)
		{
			free(minishell->envp);
			minishell->envp = NULL;	
		}
		if (minishell->local)
		{
			free(minishell->local);
			minishell->local = NULL;
		}
		if (minishell->command)
		{
			free(minishell->command);
			minishell->command = NULL;
		}
		free(minishell);
		minishell = NULL;
	}
	exit(exit_code);
}
