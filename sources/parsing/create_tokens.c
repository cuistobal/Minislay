/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:16:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 14:30:07 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static t_tokn	*create_node(char *content)
{
	t_tokn	*new;

	new = (t_tokn *)malloc(sizeof(t_tokn));
	if (new)
	{
		new->type = '\0';
		new->token = strdup(content);
		new->next = NULL;
	}
	return (new);
}

static void	append_list(t_tokn **list, t_tokn **tail, t_tokn *new)
{
	if (*list)
	{
		(*tail)->next = new;
		*tail = new;
	}
	else
	{
		*list = new;
		*tail = new;
	}
}

/*
//new
bool	create_tokens(t_tokn **tokens, t_pars *parser)
{
    t_tokn	*temp;
    t_tokn	*current;
    char	*content;

    content = the logic you have to build;
    while (content)
    {
        current = create_node(content);
		if (!current)
			return (false);
		append_list(tokens, &temp, current);
		content = my_strtok_r(NULL, " ", &save_ptr);
	}
    return (true);
}


//old
bool create_tokens(t_tokn **tokens, t_pars *parser)
{
    t_tokn	*temp;
    t_tokn	*current;
    char	*content;
    char	*save_ptr;

	save_ptr = NULL;
    content = my_strtok_r(parser->user, " ", &save_ptr);
    while (content)
    {
        current = create_node(content);
		if (!current)
			return (false);
		append_list(tokens, &temp, current);
		content = my_strtok_r(NULL, " ", &save_ptr);
	}
    return (true);
}*/

//testgpt
bool create_tokens(t_tokn **tokens, t_pars *parser)
{
	int		index;
	int		start;
    char	*token;
    t_tokn  *tempor;
    t_tokn  *current;

    if (parser && parser->user && parser->hashed)
	{
		index = 0;
		token = NULL;
		start = index;
		tempor = NULL;
    	while (parser->user[index])
    	{
			while (parser->user[index] && parser->hashed[index] == 7) //Remplacer 7
            	index++;
        	if (!parser->user[index])
            	break;
	        start = index;
   	     while (parser->user[index] && parser->hashed[index] == parser->hashed[start])
   	         index++;
   	     token = strndup(&parser->user[start], index - start);
   	     if (!token)
   	         return (false);
		 	current = create_node(token);
			free(token);
        	if (!current)
            	return (false);
        	append_list(tokens, &tempor, current);
    	}
	}
    return (true);
}
