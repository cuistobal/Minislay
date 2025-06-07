/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:37:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/04 15:55:17 by cuistobal        ###   ########.fr       */
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

static void	split_key_and_value(char *line, char **key, char **value)
{
	char	*equal;

	equal = strchr(line, '=');
	if (equal)
	{
		*equal = '\0';
		*key = strdup(line);
		*value = strdup(equal + 1);
		*equal = '=';
	}
	else
	{
		*key = strdup(line);
		*value = NULL;
	}
}

//
t_env	*create_env_node(char *line)
{
	t_env	*new;
	char	*equal;
	char	*key;
	char	*value;

	/*
	equal = strchr(line, '=');
	if (!equal)
		return (NULL);
	*equal = '\0';
	key = strdup(line);	
    if (!key)
        return (*equal = '=', NULL);
	value = strdup(equal + 1);
	*equal = '=';
	if (!value)
		return (free(key), NULL);
		*/
	split_key_and_value(line, &key, &value);
	new = malloc(sizeof(t_env));
	if (!new)
		return (free(key), free(value), NULL);
	new->var[KEY] = key;
	new->var[VALUE] = value;
	new->next = NULL;
	return (new);
}
