/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/03 09:46:01 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
t_env	*get_env_node(t_shell *minishell, char *key, char *value)
{
	t_avlt	*avlt;
	t_avlt	*node;
	t_env	*environ;

	node = NULL;
	avlt = minishell->expt;
	find_element(avlt, &node, key, value);
	if (node)
		return (node->env);	
	environ = minishell->local;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);	
	}	
	environ = minishell->command;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);	
	}	
    environ = minishell->special;
	while (environ)
	{
		if (strcmp(environ->var[KEY], key) == 0)
			return (environ);	
	}
	return (environ);
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
