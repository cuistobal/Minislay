/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:16:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/07 09:43:32 by chrleroy         ###   ########.fr       */
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
		new->token = content;
		// Do we actually need to strdup() here ?
		new->next = NULL;
	}
	return (new);
}

//This function appends the token list.
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

//This function splits the user prompt into tokens bashed on the hash code
//attributed eralier.
static bool	create_token(t_pars *parser, char **token, int *index, int start)
{
	if (parser->user[*index] && parser->hashed[*index] == parser->hashed[start])
	{
		(*index)++;
		return (create_token(parser, token, index, start));
	}
 	*token = strndup(&parser->user[start], *index - start);
	return (*token != NULL);
}

//This function performs recursive calls to skip whitespaces between tokens. Whitespaces within
//parenthesis don't get skipped.
static bool	whitespace_collapsing(char *user, uint8_t *hashed, int *index)
{
	if (user[*index] && hashed[*index] == 7) // Remplacer 7
	{
		(*index)++;
		return (whitespace_collapsing(user, hashed, index));
	}
	return (user[*index] != '\0');
}

//TEST
bool	build_token_list(t_tokn **tokens, t_pars *parser, int len)
{
	int		index;
    char	*token;
    t_tokn  *tempor;
    t_tokn  *current;

    if (parser && parser->user && parser->hashed)
	{
		index = 0;
		token = NULL;
		tempor = NULL;
    	while (index < len)
    	{
			if (whitespace_collapsing(parser->user, parser->hashed, &index))
			{
				if (create_token(parser, &token, &index, index))
				{
					current = create_node(token);
	        		if (current)
    	    			append_list(tokens, &tempor, current);
					//Malloc protection.
				}
			}
		}
	}
    return (true);
}

/*
//Old -> works
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
			//Skip whitespaces // whitespaces collapsing
			while (parser->user[index] && parser->hashed[index] == 7) //Remplacer 7
            	index++;
        	if (!parser->user[index])
            	break;
			//
			//
			//Create Token
	        start = index;
   	     	while (parser->user[index] && parser->hashed[index] == parser->hashed[start])
   	        	index++;
   	     	token = strndup(&parser->user[start], index - start);
   	     	if (!token)
   	        	return (false);
			//
			//
			//Insert Token
			current = create_node(token);
			free(token);
        	if (!current)
            	return (false);
        	append_list(tokens, &tempor, current);
    	}
	}
    return (true);
}*/
