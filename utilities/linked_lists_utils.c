/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:43:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 16:44:13 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h" 

void	append_exec_list(t_exec **head, t_exec **tail, t_exec *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
}

void	append_token_list(t_tokn **head, t_tokn **tail, t_tokn *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = (*tail)->next;
	}
}
