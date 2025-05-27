/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:40:10 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 10:26:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	add_key_to_local(t_shell **minishell, t_tokn *assignations)
{
	t_env	*local;
	t_env	*ahead;
	t_env	*atail;
	t_env	*new_element;

	ahead = NULL;
	atail = NULL;
	while (assignations)
	{
		new_element = create_env_node(strdup(assignations->value)); 
		insert_env_node(&ahead, &atail, new_element);
		move_pointer(&assignations);
	}
	local = (*minishell)->local;
	atail->next = local;
	(*minishell)->local = ahead;
}

// This function sends the assignation token to the local env list.
void	handle_assignations(t_shell **minishell, t_tokn **source)
{
	t_tokn	*copy;
	t_tokn	*expand_tail;
	t_tokn	*expand_head;
	t_tokn	*assignation_tail;
	t_tokn	*assignation_head;

	if (!source || !*source)
		return ;
	copy = *source;
	expand_tail = NULL;
	expand_head = NULL;
	assignation_head = NULL;
	assignation_tail = NULL;
	while (copy)
	{
		if (is_state_active(copy->type, EQUL))
			append_token_list(&assignation_head, &assignation_tail, copy);	
		else	
			append_token_list(&expand_head, &expand_tail, copy);
		copy = copy->next;
	}
	if (expand_head)
		*source = expand_head;
	if (expand_tail)
		expand_tail->next = NULL;	
	if (assignation_tail)
		assignation_tail->next = NULL;
}
