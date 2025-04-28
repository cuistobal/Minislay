/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_queues.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:11:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 11:16:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	redirection_queue(t_tokn *redirections)
{
	t_tokn	*in_head;
	t_tokn	*in_tail;
	t_tokn	*out_head;
	t_tokn	*out_tail;

	in_head = NULL;
	in_tail = NULL;
	out_head = NULL;
	out_tail = NULL;
	while (redirections)
	{
		if (is_state_active(redirections->type, IRED | ARED))
		{
			insert_token
		}
		else
		{
		}
	}
}
