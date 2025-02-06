/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:59:00 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 10:41:42 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	push(t_pars *parser, char c)
{
    char	*new_stack;
    int		new_capacity;

	new_stack = NULL;
	new_capacity = 0;
    if (parser->top >= parser->capacity)
	{
        new_capacity = parser->capacity + 1;
        new_stack = realloc(parser->stack, new_capacity); //Remplacer par ft_realloc
    	if (new_stack)
		{
			parser->stack = new_stack;
			parser->capacity = new_capacity;
		}
		//error_code -> mem alloc failed.
		//exit() || return() (?)
	}
	parser->stack[parser->top++] = c;
}

//
char	pop(t_pars *parser)
{
    if (parser->top > 0)
        return parser->stack[--parser->top];
    return '\0';
}

//
char	peek(t_pars *parser)
{
    if (parser->top > 0)
        return parser->stack[parser->top - 1];
    return '\0';
}
