/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:53:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 16:34:08 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//We use this function to split the token lists into sublists separated by the
//current most meaningfull grammar operator
void	delete_links(t_pars *parser)
{
	if (parser->tab[TTPREV])
		parser->tab[TTPREV]->next = NULL;
	if (parser->tab[TTCURR])
		parser->tab[TTCURR]->next = NULL;
}

//This function saves the positions of current and sets it to ->next
bool	consume_token(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		append_token_tab(parser->tab, *current, TTPREV);
		*current = (*current)->next;
		append_token_tab(parser->tab, *current, TTCURR);
		if (*current)
			return (append_token_tab(parser->tab, (*current)->next, TTNEXT));
		return (append_token_tab(parser->tab, NULL, TTNEXT));
	}
	return (false);
}

//Assesses if the lexeme's value falls within the set range 
bool	valid_lexeme(t_tokn *current, int min, int max)
{
	return (current && (current->type >= min && current->type <= max));
}
