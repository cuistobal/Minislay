/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:40:10 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/21 14:24:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	add_key_to_local(t_shell **minishell, t_tokn *assignations)
{
	return ;	
}

// This function sends the assignation token to the local env list.
void	handle_assignations(t_shell **minishell, t_tokn *source, t_tokn **assignation, t_tokn **expansions)
{
	t_tokn	*copy;
	t_tokn	*etail;
	t_tokn	*atail;

	atail = NULL;
	etail = NULL;
	copy = source;
	while (copy)
	{
		if (is_state_active(copy->type, EQUL))
			append_token_list(assignation, &etail, copy);	
		else	
			append_token_list(expansions, &atail, copy);	
		copy = copy->next;
	}
}
