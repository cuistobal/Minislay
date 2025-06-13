/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 15:46:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
//Make a choice between dup() the value of assign the current memory area.
//Since the tokenize function already dup()'s the original memory area, does it
//make sens to dup() again ?
//Also, do we make this bad boi static or do we eexpect to use it at some other
//point of the programm ?
t_tokn	*create_token_node(char *value, int type)
{
	t_tokn	*node;

	node = NULL;
	if (!value)
		return (NULL);
	node = (t_tokn *)malloc(sizeof(t_tokn));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->next = NULL;
	return (node);
}

//This utility inserts the new token inside the token_list.
//Do we make this one static ?
void	insert_token(t_tokn **head, t_tokn **current, t_tokn **new_node)
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

//We use this function to keep track of closed && unclosed parenthesis.
bool	get_stacked(t_tokn **head, t_tokn *current, int *mask)
{
	static int	count;

	if (head && !*head)
	{
		count = -1;
		*mask = INIT;
	}
	if (!current)
		return (count < 0);
	if (current->type == OPAR)
	{
		count++;
		*mask = OPAR;
	}
	else if (current->type == CPAR)
	{
		if (count < 0)
			return (false);
			//	error_message(SYNTAX), error_message(UNMATCHED_PAR));
		count--;
		if (count < 0)
			*mask = INIT;
	}
	return (true);
}

//This function creates a token node and assigns it the token value & type 
//passed as parameter.
bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type)
{
	static int	mask;
	t_tokn		*new_node;

	new_node = create_token_node(token, type);
	if (new_node)
	{
		if (get_stacked(head, new_node, &mask))
		{
			if (!(new_node->type & mask))
				set_state(&(new_node)->type, mask);
			return (insert_token(head, current, &new_node), true);
		}	
		return (error_message(SYNTAX), error_message(UNMATCHED_PAR));
	}
	return (false);
}
