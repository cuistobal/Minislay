/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:34:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/01 17:37:36 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_module.h"

t_tokn  *create_token_node(char *content, char type)
{
    t_tokn  *new;

    new = (t_tokn *)malloc(sizeof(t_tokn));
    if (new)
    {
        new->type = type;
        new->content = content;
        new->next = NULL;
    }
    return (new);
}

bool    create_token_node_and_append_list(t_tokn **list, char *token)
{
    t_tokn  *new;

    new = create_token_node(token, 0);
    if (new)
    {
        if (*list)
        {
            (*list)->next = new;
            *list = (*list)->next;
        }
        else
            (*list) = new;
        return (true);
    }
    return (false);
}

bool    tokenize_user_input(t_tokn **list, char *input, char *separator)
{
    char    *token;

    if (input)
    {
        token = strtok(input, separator);
        while (token)
        {
            if (create_token_node_and_append_list(list, token))
                token = strtok(NULL, separator);
            else
                return (false);
        }
        return (true);
    }
    return (false);
}
