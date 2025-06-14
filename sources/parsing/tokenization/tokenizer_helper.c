/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 14:39:22 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	syntax_error(char buffer[])
{
	error_message(BASH);
	error_message(UNEXPECTED);
	error_message(buffer);
	return (error_message("\n"));
}

bool	tokenizer_helper(char *prev, char current)
{
	char	imasavage[2];

	if (current)
		imasavage[0] = current;
	else
		imasavage[0] = *prev;
	imasavage[1] = 0;
	if (current && is_redir(*prev))
		return (*prev = INIT, syntax_error(imasavage));
	else if (is_paren(*prev) && is_paren(current) && current != *prev)
		return (*prev = INIT, syntax_error(imasavage));
	else if (!current && (prev && *prev != ')'))
		return (*prev = INIT, syntax_error(imasavage));
	return (true);
}

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
