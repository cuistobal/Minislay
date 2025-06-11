/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 16:53:56 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

t_env	*get_env_node(t_shell *minishell, char *key, char *value)
{
	t_env	*environ;

	environ = minishell->envp;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);
		move_env_pointer(&environ);
	}	
	environ = minishell->local;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);
		move_env_pointer(&environ);
	}	
	environ = minishell->command;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);
		move_env_pointer(&environ);
	}
	return (NULL);
}

//
t_env	*get_env_tail_node(t_env *list)
{
	t_env	*tail;

	tail = NULL;
	while (list)
	{
		tail = list;
		list = list->next;
	}
	return (tail);
}
