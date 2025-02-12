/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/12 14:42:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
static t_tokn	*create_node(char *value, int type)
{
    t_tokn *node;

	if (value)
	{
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
	}
	return (NULL);
}

//Ongoing development on this bad boi


//We use this function in case we get a variable expansion within our 
static bool	split_token(t_tokn **token, char *sub_token, int sub_type)
{
	t_tokn	*new;
	t_tokn	*next;

	new = create_node(sub_token, sub_type);
	if (new)
	{
		next = (*token)->next;
		(*token)->next = new;
		new->next = next;
		*token = (*token)->next;
	}
	return (new != NULL);
}

//Used to asses if a " token needs further spliting for interpretation, 
//assignement and expenasion during the execution phase.
static bool	assess_dquote_token(t_tokn **token)
{
	int		index;
	char	sub_type;
	char	*sub_token;

	index = 0;
	if ((*token))
	{
		//We need to handle "$*" && '=' differently, since we need to "bactrack"
		//to the previous whitespace in case we find a '='.
		//We also need to check if there is a whitespace after the '$' block
		//We should probably run strtok here.
		//
		//After testing assignations && * expansions doesnt work within "". The
		//$ expansions do expand though.
		//
		sub_token = strdup(strpbrk((*token)->value, IAE));
		if (sub_token)
		{
			sub_type = *sub_token;
			while ((*token)->value[index] &&(*token)->value[index] != sub_type)
				index++;
			//What is IAE is the first character ? -refer to test case-
			(*token)->value = realloc((*token)->value, sizeof(char) * index);
			return (split_token(token, sub_token, sub_type));
		}
	}
	return (false);
}

/*
//Modifier pour bosser avec un int a la place
static int	get_token_type(char *token)
{
	int		code;
	char	type;
	char	*grammar;

	code = 0;
	type = '\0';
	grammar = NULL;
	if (token)
	{
		type = token[0];
		grammar = strchr(GRAMMAR, type);
		if (grammar)
		{
			code =
			return (code);
		}
		return (WORD);
	}
	return (code);
}*/
//We use this function to construct our initial token_list
//
//Modifs -> include char *type in the function parameter to get a real type
//instead of "token".
bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type)
{
	t_tokn	*new_node;

	new_node = create_node(token, type);
	if (new_node)
	{
        if (!(*head))
			*head = new_node;
        else
			(*current)->next = new_node;
        *current = new_node;
	}
	return (new_node != NULL);
}
