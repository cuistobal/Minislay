/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 09:37:07 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
bool	insert_env_node(t_env **head, t_env **tail, t_env *new)
{
	if (!new)
		return (false);
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
	return (true);
}

//
t_env	*create_env_node(char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var[KEY] = strtok_r(value, "=", &value);
	new->var[VALUE] = value;
	new->next = NULL;
	return (new);
}
