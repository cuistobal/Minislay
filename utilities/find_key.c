/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:21:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:33:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	find_key_in_avlt(t_avlt *tree, char **value, char *key)
{
	t_avlt	*node;

	node = NULL;
	if (!tree)
		return (false);
	find_element(tree, &node, key, *value);
	if (node)
		return (*value = node->env->var[VALUE], true);
	return (false);
}

//
static bool	find_key_in_local(t_env *local, char **value, char *key)
{
	while (local)
	{
		if (strcmp(local->var[KEY], key) == 0)
		{
			*value = local->var[VALUE];
			return (true);
		}
		move_env_pointer(&local);
	}
	return (false);
}

//
static bool	find_key_in_command(t_env *command, char **value, char *key)
{
	while (command)
	{
		if (strcmp(command->var[KEY], key) == 0)
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
	t_avlt	*root;
	t_env	*head;

	if (!minishell)
		return (false);
	root = minishell->expt;
	if (find_key_in_avlt(root, value, key))
		return (*value);
	head = minishell->local;
	if (find_key_in_local(head, value, key))
		return (*value);
	head = minishell->command;
	if (find_key_in_command(head, value, key))
		return (*value);
	return (false);
}
