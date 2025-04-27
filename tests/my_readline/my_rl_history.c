/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:10:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 14:49:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"

void	my_add_history(t_rlhs **head, t_rlhs **tail, char *line)
{
	t_rlhs	*new;

	new = (t_rlhs *)malloc(sizeof(t_rlhs));
	if (!new)
		return ;
	new->line = strdup(line);	
	if (!new->line)
		return (free(new));
	new->next = NULL;
	new->prev = NULL;
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
	}
}
