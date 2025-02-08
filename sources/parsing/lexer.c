/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 12:08:28 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool	init_stack(t_stck *stack, int size)
{
    stack->infos[0] = -1;
	stack->infos[1] = size;
	stack->stack = (char *)malloc(size * sizeof(char));
	return (stack->stack != NULL);
}

static bool push(t_stck *stack, char c)
{
    if (stack->infos[0] < stack->infos[1] - 1)
	{
        stack->stack[++(stack->infos[0])] = c;
        return (true);
    }
	else
	{
		stack->stack = realloc(stack->stack, stack->infos[1] + 2);
		if (stack->stack)
			return (push(stack, c));
	}
    return (false);
}

static bool pop(t_stck *stack)
{
    if (stack->infos[0] >= 0)
	{
        (stack->infos[0])--;
        return (true);
    }
    return (false);
}

static bool handle_parentheses(t_stck *stack, char *string)
{
    if (strcmp(string, "(") == 0)
        return (push(stack, '('));
    else if (strcmp(string, ")") == 0)
        return (pop(stack));
    return (true);
}

bool	lexer(t_tokn *head)
{
	bool	ans;
	t_stck	stack;
    t_tokn	*current;

	current = head;
    init_stack(&stack, 2);
    printf("%d	%d	%s\n", stack.infos[0], stack.infos[1], stack.stack);
	while (current)
	{
		if (strcmp(current->value, "(") == 0 && strcmp(current->value, ")") == 0)
		{
			if (!handle_parentheses(&stack, current->value))
				return (free(stack.stack), false);
		}
		else if (strcmp(current->value, "&&") == 0 || strcmp(current->value, "||") == 0)
		{
            if (!current->next || strcmp(current->next->type, "Token") != 0)
				return (false);
        } 
		else if (strcmp(current->value, ">") == 0 || strcmp(current->value, ">>") == 0 || strcmp(current->value, "<") == 0  || strcmp(current->value, "<<") == 0)
		{
            if (!current->next || strchr("&|()<>", current->next->value[0]))
				return (false);
        }
        current = current->next;
    }
	ans = stack.infos[0] == -1;
    printf("%d	%d	%s\n", stack.infos[0], stack.infos[1], stack.stack);
	return (free(stack.stack), ans);
}
