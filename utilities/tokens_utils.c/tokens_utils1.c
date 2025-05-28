/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:01:41 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/28 15:38:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//This function frees the token list passed as parameter
void	free_tokens(t_tokn *tokens)
{
	t_tokn *temp;

	temp = NULL;
	if (!tokens)
		return ;
	while (tokens)
	{
		temp = (tokens)->next;
		if ((tokens)->value)
		{
			free((tokens)->value);
			(tokens)->value = NULL;
		}
		free(tokens);
		tokens = temp;
	}
}

