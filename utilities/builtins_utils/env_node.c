/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 17:14:43 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
bool	insert_env_node(t_env **head, t_env **tail, t_env *new)
{
	if (!new || !head)
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
t_env	*create_env_node(t_env **prev, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var[KEY] = strtok_r(value, "=", &value);
	new->var[VALUE] = value;
	new->next = NULL;
	if (!*prev)
		*prev = new;
	else
	{
		(*prev)->next = new;
		*prev = (*prev)->next;
	}
	return (new);
}
