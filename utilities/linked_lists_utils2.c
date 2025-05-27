/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:18:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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
