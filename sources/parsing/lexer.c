/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 14:14:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Function to free the stack and handle errors
static bool free_stack(t_stck **stack)
{
    bool status;

    status = false;
    if (*stack)
	{
        if ((*stack)->stack)
		{
            if ((*stack)->top >= 0)
                printf("Syntax error: Unclosed %c\n", (*stack)->stack[(*stack)->top]);
            else
                status = true;
            free((*stack)->stack);
        }
        free(*stack);
        *stack = NULL;
    }
    return (status);
}

// Function to initialize the stack
static bool init_stack(t_stck **stack, size_t size)
{
    if (size > 0)
	{
        *stack = (t_stck *)malloc(sizeof(t_stck));
        if (*stack)
		{
            (*stack)->top = -1;
			(*stack)->capacity = size;
			(*stack)->stack = (char *)calloc(size, sizeof(char));
        	return (*stack->stack != NULL);
		}
    }
    return (*stack != NULL);
}

// Function to push a character onto the stack
static bool push(t_stck *stack, char c)
{
    if (stack->top < stack->capacity - 1)
	{
        stack->stack[++(stack->top)] = c;
        return true;
    }
	else
	{
        stack->capacity += 2;  // Increase the capacity
        stack->stack = realloc(stack->stack, stack->capacity);
        if (stack->stack)
            return (push(stack, c));
    }
    return (false);
}

// Function to pop a character from the stack
static bool pop(t_stck *stack)
{
    if (stack->top >= 0)
	{
        stack->stack[stack->top--] = '\0';  // Clear the popped element
        return (true);
    }
    return (false);
}

// Function to handle parentheses
static bool handle_parentheses(t_stck *stack, char type)
{
    if (type == '(')
        return (push(stack, '('));
    else
	{
        if (stack->top >= 0 && stack->stack[stack->top] == '(')
            return (pop(stack));
        else
		{
            printf("Syntax error: Unmatched closing parenthesis\n");
            return (false);
        }
    }
}

// Lexer function
bool lexer(t_tokn current*)
{
    t_stck *stack;

    if (init_stack(&stack, STACK_SIZE))
	{
	    while (current)
		{
	        if (is_paren(current->value[0]))
			{
	            if (!handle_parentheses(stack, current->value[0]))
					return (free_stack(&stack));
	        }
			else if (is_amp_pipe(current->value[0]))
			{
	            if (!current->next || is_amp_pipe(current->next->value[0]))
					return (free_stack(&stack));
	        }
			else if (is_redir(current->value[0]))
			{
				if (!current->next || strchr("&|()<>", current->next->value[0]))
					return (free_stack(&stack));
	        }
   	    current = current->next;
   		}
	}
	return (free_stack(&stack));
}
