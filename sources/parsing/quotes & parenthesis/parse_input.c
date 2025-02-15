/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:33:01 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/04 08:55:08 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool	check_parser_status(t_pars *parser)
{
	if (is_state_active(&parser, STATE_SINGLE_QUOTE))
	{
		free(parser->stack);
		free(parser);
		//error meesage single quote
		return (false);
	}
    else if (is_state_active(&parser, STATE_DOUBLE_QUOTE))
	{
		free(parser->stack);
		free(parser);
		//error message double quote
		return (false);
	}
	else if (is_state_active(&parser, STATE_SUBSHELL))
	{
		free(parser->stack);
		free(parser);
		//error message parenthesis
		return (false);
	}
	return (true);
}

static bool	parser_initialisation(t_pars *parser)
{
	if (!parser)
	{
		parser = (t_pars *)malloc(sizeof(t_pars));
		if (parser)
		{
    		parser->state = STATE_NORMAL;
    		parser->top = 0;
			parser->capacity = 1;
			parser->stack = malloc(parser.capacity);
			if (parser->stack)
			{
				parser.stack[parser.top] = '\0';
				return (true);
			}
			//error_code -> mem alloc failed.
			free (parser);
		}
		//error_code -> mem alloc failed.
		return (false);
	}
	//error_code -> mem already allocated.
	return (false);
}

bool parse_input(const char *input)
{
	size_t		index;
    t_parser	parser;

	parser = NULL;
	if (parser_initialisation(&parser))
	{
		index = 0;
		while (input[i])
		{
            if (!handle_char(&parser, input[i]))
			{
				free(parser.stack);
				free(parser);
				return (false);
			}
            index++;
		}
		return(check_parser_status(&parser));
	}
	return (false);
}
