/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/16 08:38:23 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
t_tokn	*create_node(char *value, int type)
{
    t_tokn *node;

	node = NULL;
	if (value)
	{
		node = (t_tokn *)malloc(sizeof(t_tokn));
		if (node)
		{
    		node->type = type;
			node->value = strdup(value);
			node->next = NULL;
		}
	}
	return (node);
}

static void	insert_token(t_tokn **head, t_tokn **current, t_tokn **new_node)
{
	if (*new_node)
	{
		if (!(*head))
			*head = *new_node;
    	else if (*current)
			(*current)->next = *new_node;
    	*current = *new_node;
	}
}

bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type)
{
	t_tokn	*new_node;

	new_node = create_node(token, type);
	if (new_node)
	{
		insert_token(head, current, &new_node);
	//	if (new_node->type == EQUL)
	//		split_assignation_token(&new_node);
//		if (new_node->type & WORD)
//			check_word_content(&new_node);
//		check_sub_tokens(current);
    }
    return (new_node != NULL);
}
