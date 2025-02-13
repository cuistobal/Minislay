/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:32 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/13 11:57:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static char	*find_delimiter(char *origin, char *delimiter)
{
	char	*sub_token;

	sub_token = strpbrk(origin, delimiter);
	return (sub_token);
}

void	check_word_content(t_tokn **assessed)
{
	char	*delimiter;
	char	*sub_token;

	sub_token = NULL;
	if (*assessed)
	{
		if ((*assessed)->type & DQTE)
		{
			sub_token = find_delimiter((*assessed)->value), delimiter);
			if ()
			{
				new = ;
				(*assessed)->next = new;
				*assessed = new;
				check_word_content(assessed);
			}
		}
		else
		{

		}
	}
}
