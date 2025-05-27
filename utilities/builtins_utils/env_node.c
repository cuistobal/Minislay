/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 10:24:17 by chrleroy         ###   ########.fr       */
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
t_env	*create_env_node(char *line)
{
	t_env	*new;
	char	*equal;
	char	*key;
	char	*value;

	equal = strchr(line, '=');
	if (!equal)
		return (NULL);
	*equal = '\0';
	key = strdup(line);
	value = strdup(equal + 1);
	*equal = '=';

	if (!key || !value)
		return (free(key), free(value), NULL);

	new = malloc(sizeof(t_env));
	if (!new)
		return (free(key), free(value), NULL);
	new->var[KEY] = key;
	new->var[VALUE] = value;
	new->next = NULL;
	return (new);
}
