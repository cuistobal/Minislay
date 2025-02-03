/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_parenthesis_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:35:05 by chrleroy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/03 08:04:38 by chrleroy         ###   ########.fr       */
=======
/*   Updated: 2025/02/03 09:27:18 by chrleroy         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

<<<<<<< HEAD
static bool	stack_handler(char *stack, char input)
=======
static bool	pop()
>>>>>>> main
{
	if (stack)
	{

<<<<<<< HEAD
=======
	}
	return false;
}

static bool	top()
{
	stack = ft_realloc();
	stack[] = ;
}

static bool	stack_handler(char *stack, char input)
{
	if (stack)
	{
		
>>>>>>> main
		return ();
	}
	return ();
}

static bool	is_syntax(char *syntax, char input)
{
	int	i;

	if (syntax)
	{
		i = 0;
		while (syntax[i])
		{
			if (syntax[i] == input)
				return (true);
		}
	}
	return (false);
}

//
<<<<<<< HEAD
bool	matching_syntax(char *input, char *syntax)
{
	int		i;
	char	*stack;
	
	if (input && syntax)
=======
bool	matching_syntax(t_pars	*parser)
{
	int		i;
	
	if (parser->input && parser->syntax)
>>>>>>> main
	{
		i = 0;
		stack = NULL;
		while (input[i] != '\0')
		{
			if (is_syntax(syntax, input[i]))
				stack_handler(stack, input[i])
			i++;
		}
		if (stack)
			return (free(stack), false);
	}
	return (false);
}
