/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:21:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:25:45 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
bool	find_key_in_env(t_env *command, char **value, char *key)
{
	while (command)
	{
		if (ft_strcmp(command->var[KEY], key) == 0)
		{
			*value = command->var[VALUE];
			return (true);
		}
		move_env_pointer(&command);
	}
	return (false);
}

//Looking for the $KEY, so we can acess its value. If $KEY isn't found, we 
//return false;
bool	find_key(t_shell *minishell, char **value, char *key)
{
	t_env	*head;

	if (!minishell)
		return (false);
	head = minishell->envp;
	if (find_key_in_env(head, value, key))
		return (*value);
	head = minishell->local;
	if (find_key_in_env(head, value, key))
		return (*value);
	head = minishell->command;
	if (find_key_in_env(head, value, key))
		return (*value);
	head = minishell->special;
	if (find_key_in_env(head, value, key))
		return (*value);
	return (false);
}
