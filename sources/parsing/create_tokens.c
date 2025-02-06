/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:16:17 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 14:07:19 by chrleroy         ###   ########.fr       */
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

//
bool	create_tokens(t_tokn **tokens, t_pars *parser)
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
}

/*
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
