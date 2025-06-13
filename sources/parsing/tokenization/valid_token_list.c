/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:22:27 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 10:27:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	valid_token_list(t_tokn *list)
{
	int		count;
	t_tokn	*current;

	count = 0;
	current = list;
	while (current)
	{
		move_pointer(&current);
		count++;
	}
	return (count > 1 || !valid_lexeme(list, HDOC, ARED));
}
