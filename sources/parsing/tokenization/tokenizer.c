/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:17:21 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 09:35:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static t_tokn	*create_tokens(char *token, char type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new)
	{
		new->type = type;
		new->token = token;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}



//We use this function to turn the pre parsed input && hashed version into a 
//token list.
bool	tokenizer(t_token *tokens, char *input, uint8_t *hashed)
{
	size_t	index;
	t_token	*current;

	current = NULL;
	if (input && hashed)
	{
		index = 0;
		while (input[i] && hashed[i])
		{
			//Logique

			//Append_list
			if (!tokens)
			{
				tokens = create_token();
				if (tokens)
					current = tokens->next;
				else
					return (false); // Error code -> Invalid allocation.
			}
			else
			{
				if (!current)

			}
		}
		return (true);
	}
	// Error code -> Invalid memmory address
	return (false);
}
