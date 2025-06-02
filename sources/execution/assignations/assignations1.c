/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:40:10 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/02 10:12:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	add_key_to_local(t_shell **minishell, t_tokn *assignations)
{
	char	*key;
	char	*value;
	t_env	*ltail;
	t_env	*new_element;

	ltail = get_env_tail_node((*minishell)->local);
	while (assignations)
	{
		//If not in en already ->
		if (!)
		{
			new_element = create_env_node(strdup(assignations->value));
			insert_env_node(&(*minishell)->local, &ltail, new_element);
		}
		//Else append value
		else

		move_pointer(&assignations);
	}
}
