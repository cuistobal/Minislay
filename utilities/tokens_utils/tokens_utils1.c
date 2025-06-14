/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:01:41 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 09:56:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	free_token_nodes(t_tokn *token)
{
	t_tokn	*next;

	while (token)
	{
		next = token->next;
		free(token);
		token = next;
	}
}

//This function frees the token list passed as parameter
void	free_tokens_adress(t_tokn **tokens)
{
	t_tokn	*temp;

	temp = NULL;
	if (!*tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		if ((*tokens)->value != NULL)
		{
			free((*tokens)->value);
			(*tokens)->value = NULL;
		}
		free(*tokens);
		*tokens = NULL;
		*tokens = temp;
	}
	*tokens = NULL;
}

//This function frees the token list passed as parameter
void	free_tokens(t_tokn *tokens)
{
	t_tokn	*temp;

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
	tokens = NULL;
}
