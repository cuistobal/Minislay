/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:55:58 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 09:38:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Appends the parser's token tab and returns true
bool	append_token_tab(t_tokn *tab[], t_tokn *pointer, int token_type)
{
	tab[token_type] = pointer;
	return (true);
}

//
bool	reset_parser(t_pars *parser, t_tokn *token, int i, t_tree **branch)
{
	int	index;

	if (parser)
	{
		index = 0;
		while (index < TTSIZE)
		{
			(parser)->tab[index] = NULL;
			if (index == i)
				(parser)->tab[index] = token;
			index++;
		}
		if ((parser)->state & SUBSHEL)
			(parser)->state = SUBSHEL;
		else
			(parser)->state = INITIAL;
		(parser)->ast = branch;
		return (true);
	}
	return (false);
}

//Allocate memory for the parsing structure && initialiase its variables.
//Returns false if malloc fails.
t_pars	*define_parser(t_tree **ast, t_tokn *tokens)
{
	t_pars	*parser;

	parser = (t_pars *)malloc(sizeof(t_pars));
	if (!parser)
		return (NULL);
	parser->state = INITIAL;
	append_token_tab(parser->tab, tokens, TTHEAD);
	append_token_tab(parser->tab, NULL, TTPREV);
	append_token_tab(parser->tab, NULL, TTCURR);
	append_token_tab(parser->tab, NULL, TTNEXT);
	parser->ast = ast;
	return (parser);
}
