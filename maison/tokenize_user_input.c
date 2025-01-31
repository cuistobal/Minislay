/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:34:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/01/31 12:08:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct  token
{
    char            type;
    char            *content;
    struct  token   *next;
}   t_tokn;

t_tokn  create_token_node(char *content, char type)
{
    t_tokn  *new;

    new = (t_tokn *)malloc(sizeof(t_tokn));
    if (new)
    {
        new->type = type;
        new->content = content;
        next = NULL;
    }
    return (new);
}

bool    create_token_node_and_append_list()
{
    t_tokn  *new;

    new = create_token_node();
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

bool    tokenize_user_input(t_tokn **list, char *input)
{
    int index;

    if (input)
    {
        index = 0;
        while (input[index] != '\0')
        {
            if (is_space(input[index]))
            {
            }
        }
        return (true);
    }
    return (false);
}
