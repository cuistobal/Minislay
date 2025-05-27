/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:40:10 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/27 12:59:10 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	add_key_to_local(t_shell **minishell, t_tokn *assignations)
{
	t_env	*ltail;
	t_env	*new_element;

	ltail = get_env_tail_node((*minishell)->local);
	while (assignations)
	{
		new_element = create_env_node(strdup(assignations->value));
		insert_env_node(&(*minishell)->local, &ltail, new_element);
		move_pointer(&assignations);
	}
}
