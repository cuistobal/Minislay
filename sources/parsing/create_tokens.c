/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 13:53:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
static t_tokn	*create_node(char *type, char *value)
{
    t_tokn *node;

	node = (t_tokn *)malloc(sizeof(t_tokn));
	if (node)
	{
    	node->type = type;
		//node->value = value ? strdup(value) : NULL;
		node->value = strdup(value);	//node->value = value ? strdup(value) : NULL;
										//Needs to be tested with NULL value
										//(Case shouldn't occur though)
    	node->next = NULL;
    	return (node);
	}
	return (NULL);
}

//We use this function to construct our initial token_list
//
//Modifs -> include char *type in the function parameter to get a real type
//instead of "token".
bool	create_new_token(t_tokn **head, t_tokn **current, char *token)
{
	t_tokn *new_node;

	new_node = create_node("Token", token);
	if (new_node)
	{
        if (!(*head))
			*head = new_node;
        else
			(*current)->next = new_node;
        *current = new_node;
		return (true);
	}
	return (false);
}
