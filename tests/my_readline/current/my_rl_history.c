/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:10:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/29 09:12:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"
i
//
void	my_add_history(t_rlhs **history, char *line)
{
	t_hist	*new;

	new = (t_hist *)malloc(sizeof(t_hist));
	if (!new)
		return ;
	new->line = strdup(line);
	if (!new->line)
		return (free(new));
	new->next = NULL;
	new->prev = NULL;
	if (!(*history)->head)
	{
		(*history)->head = new;
		(*history)->tail = new;
		(*history)->current = new;
	}
	else
	{
		new->prev = (*history)->tail;
		(*history)->tail->next = new;
		(*history)->current = new;
	}
}

//
void	navigate_history(t_rlhs **history, bool uparrow, char **line)
{
	char	*temp;

	temp = NULL;
	if (!(*history) || !(*history)->head)
		return ;
	if ((*history)->current)
	{
		if (uparrow)
		{
			temp = (*history)->current->line;
			if (temp)
			
			write(1, (*history)->current->line, strlen((*history)->current->line));

			(*history)->current = (*history)->current->prev;							
		}
		else
		{
			write(1, (*history)->current->line, strlen((*history)->current->line));
			(*history)->current = (*history)->current->next;
		}
	}	
}

//
t_rlhs	*create_history_node(void)
{
	t_rlhs	*history;

	history = (t_rlhs *)malloc(sizeof(t_rlhs));
	if (!history)
		return (NULL);
	history->head = NULL;
	history->tail = NULL;
	history->current = NULL;
	return (history);
}
