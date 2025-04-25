/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/25 11:42:15 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Prints the environement variables
void	env(t_shel *minishell)
{
	t_env	*current;

	if (!minishell || !minishell->envp)
	{
		error_message("No env\n");
		return ;
	}
	current = minishell->envp; 
	while (current)
    {
		write(1, current->var[0], strlen(current->var[0]));
		write(1,"=", 1);
		write(1, current->var[1], strlen(current->var[1]));
		write(1,"\n", 1);
        current = current->next;
    }
}
