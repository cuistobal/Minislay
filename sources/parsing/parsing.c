/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:39:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/07 09:42:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void	initialise_check_type(bool (*check[9])(char))
{
   	check[0] = is_paren;
	check[1] = is_amp_pipe;
    check[2] = is_iredir;
    check[3] = is_oredir;
    check[4] = is_squotes;
    check[5] = is_dquotes;
    check[6] = is_var_wild;
    check[7] = is_whitespace;
}

//
static void	initialise_syntax(char syntax[])
{
	syntax[0] = OPAR;
	syntax[1] = SQTE;
	syntax[2] = DQTE;
	syntax[3] = CPAR;
}

//We use this function to allocate & initialise the memory of the parsing
//structure
static t_pars	*initialise_parsing_structure(int len)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (new)
	{
		new->user = (char *)calloc(len, sizeof(char));
		if (new->user)
		{
			new->hashed = (uint8_t *)calloc(len, sizeof(uint8_t));
			if (new->hashed)
			{
				new->stack = NULL;
				initialise_syntax(new->syntax);
				initialise_check_type(new->check_type);
				new->state = STATE_NORML;
				return (new);
			}
			free (new->user);
		}
		free (new);
	}
	return (NULL);
}

//We use this function to free the parsing structure and return true if parsing
//was completed sucessfully.
static bool	free_parser(t_pars *parser)
{
	bool	success;

	success = false;
	if (parser)
	{
		success = parser->state == STATE_NORML;
		if (parser->user)
		{
			free(parser->user);
			if (parser->hashed)
				free(parser->hashed);
		}
		free (parser);
	}
	return (success);
}

//This is the main parsing function
bool	parsing(t_tokn **tokens, char *input)
{
	int		len;
	int		index;
	t_pars	*parser;
	
	parser = NULL;
	if (input)
	{
		len = strlen(input);
		parser = initialise_parsing_structure(len);
		if (parser)
		{
			index = 0;
			while (index < len)
			{
				if (!handle_char(parser, input, index))
					break ;
				index++;
			}
			if (index == len)
				build_token_list(tokens, parser, len);
		}
	}
	return (free_parser(parser));
}
