/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:01:41 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 15:02:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//This function frees the token list passed as parameter
void	free_tokens(t_tokn *tokens)
{
	t_tokn *temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
		{
			free (temp->value);
			temp->value = NULL;
		}
		free (temp);
		temp = NULL;
	}
}

