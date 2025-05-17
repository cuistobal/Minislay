/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/17 14:12:04 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

int	env(t_shell *minishell, char **arguments)
{
	t_env	*current;

	if (!minishell)
		return (ERROR);
	if (arguments && arguments[0])
	{
		write(2, "env: '", 6);
		write(2, arguments[0], strlen(arguments[0]));
		write(2, "': No such file or directory\n", 30);
		return (ERROR);
	}
	current = minishell->envp; 
	while (current)
    {
		if (current->var[0] && current->var[1])
		{
			write(1, current->var[0], strlen(current->var[0]));
			write(1,"=", 1);
			write(1, current->var[1], strlen(current->var[1]));
			write(1,"\n", 1);
		}
        current = current->next;
    }
	return (SUCCESS);
}
