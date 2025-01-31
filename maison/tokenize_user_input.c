/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_user_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:34:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/01/31 12:02:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct  token
{
    char            type;
    char            *content;
    struct  token   *next;
}   t_tokn;

t_tokn  create_token_node(char *string)
{
    t_tokn  *new;

    new = (t_tokn *)malloc(ssizoef(t_tokn));
    if (new)
    {
        type = ;
        new->content = string;
        next = NULL;
    }
    return (new);
}

bool    tokenize_user_input(t_tokn **list, char *input)
{

    if (input)
    {
         
        return (true);
    }
    return (false);
}
