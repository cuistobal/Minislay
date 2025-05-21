/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:40:10 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 08:42:41 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	add_key_to_local(t_shell **minishell, t_tokn *assignations)
{
	return ;	
}

// This function sends the assignation token to the local env list.
t_tokn	*handle_assignations(t_shell **minishell, t_tokn **source)
{
	t_tokn	*copy;
	t_tokn	*tail;
	t_tokn	*expansions;

	tail = NULL;
	copy = *source;
	expansions = NULL;
	while (copy)
	{
		if (!is_state_active(copy->type, EQUL))
			append_token_list(&expansions, &tail, copy);	
		else
			add_key_to_local(minishell, copy);
		copy = copy->next;
	}
	print_tokens(expansions);
	return (expansions);
}
