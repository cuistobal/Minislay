/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/18 17:54:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
//Make a choice between dup() the value of assign the current memory area.
//Since the tokenize function already dup()'s the original memory area, does it
//make sens to dup() again ?
//Also, do we make this bad boi static or do we eexpect to use it at some other
//point of the programm ?
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
			node->value = value;
			//node->value = strdup(value);
			node->next = NULL;
		}
	}
	return (node);
}

//This utility inserts the new token inside the token_list.
//Do we make this one static ?
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


//We use this function to keep track of closed && unclosed parenthesis.
bool	get_stacked(t_tokn **head, t_tokn *current)
{
	static int	count;	

	if (!*head)
		count = 0;
	else if (current)
	{
		if ((current->type == OPAR))
			count++;
		else if (current->type == CPAR)
		{
			if (count < 0)
				return (false);
			count--;
		}
	}
	current ? printf("%d	->	%s\n", count, current->value) : printf("%d\n", count);
	return (true);
}

//This function creates a token node and assigns it the token value & type 
//passed as parameter.
bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type)
{
	t_tokn	*new_node;

	new_node = create_node(token, type);
	if (new_node)
	{
		if (get_stacked(head, new_node))
		{
			insert_token(head, current, &new_node);		
			return (true);
		}
		printf("Syntax Error, invalid parenthense.\n");
	}
	return (false);
}
