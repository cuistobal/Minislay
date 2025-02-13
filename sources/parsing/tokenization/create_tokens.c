/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:44:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/13 11:14:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Node creation util
static t_tokn	*create_node(char *value, int type)
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

//Ongoing development on this bad boi

/*
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
}*/

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
/*
static bool	check_token(t_tokn **assessed)
{
	t_tokn	*new;
	int		type;
	int		index;
	char	*token;

	if (*assessed)
	{
		token = strpbrk((*assessed)->value, IAE);

		index = 0;
		while ((*assessed)->value[index])
		{
			if (isdelim((*assessed)->value[index])
			token = ;
			type = 
			new = create_node(token, type);
			(*assessed)->next = new;
			*assessed = new;
			check_token(assessed);
		}
	}
	return (*assessed == NULL);
}*/

bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type)
{
	t_tokn	*new_node;

	new_node = create_node(token, type);
	if (new_node)
	{
//		if (type == WORD || type == DQTE || type == EQUL)
//			new_node = check_token(new_node);
		insert_token(head, current, &new_node);
    }
    return (new_node != NULL);
}
