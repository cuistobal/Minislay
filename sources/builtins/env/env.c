/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 13:06:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Prints the environement variables
int	env(t_shel *minishell, char **arguments)
{
	t_env	*current;

	if (!minishell)
		return (ERROR);
	current = minishell->envp; 
	while (current)
    {
		write(1, current->var[0], strlen(current->var[0]));
		write(1,"=", 1);
		write(1, current->var[1], strlen(current->var[1]));
		write(1,"\n", 1);
        current = current->next;
    }
	return (SUCCESS);
}
