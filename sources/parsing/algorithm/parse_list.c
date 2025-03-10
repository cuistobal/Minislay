#include "minislay.h"

static bool	ignore_nested_operators(t_tokn **current, t_pars *parser)
{
	if ((*current) && valid_lexeme(*current, LAND, LORR | OPAR))
	{
		//printf("%s	%s\n", __func__, (*current)->value);
		if ((*current)->type & OPAR)
		{
			consume_token(current, parser);
			return (parse_command_list(current, parser));
		}
		else
		{
		//	printf("%s	%s	%s\n", __func__, (*current)->value, parser->tab[TTCURR]->value);
		//	printf("%d	%d\n", (*current)->type, LAND);
			set_state(&parser->state, ROOTEDD);
			return ((*current)->next);
		}
	}
	return (*current);
}

static void	handle_subshells(t_tokn **current, t_pars *parser)
{
	t_tokn	*temp;
	t_tokn	*subshell;

	temp = NULL;
	subshell = NULL;
	while ((*current) && (*current)->type & CPAR)
	{
		if ((*current)->next)
		{
			if (!((*current)->next->type & CPAR) && (*current)->next->type >= WORD)
			{
				subshell = create_token_node(strdup(SUBSHELL), LAND);
				if (subshell)
				{
					temp = (*current)->next;
					(*current)->next = subshell;
					subshell->next = temp;
				}
			}
		}
		consume_token(current, parser);
	}
}

//This function identifies command blocks that will later be the AST'S elements 
bool	parse_command_list(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (parse_command(current, parser))
		{
			if (*current)
			{
				handle_subshells(current, parser);
				return (ignore_nested_operators(current, parser));
			}
		}
	}
	return (!*current);
}

//This is the entry of our parsing module. It identifies the first non 
//parethesed significant operator and builds the tree's root out of it
bool	parse_script(t_pars **parser)
{
	t_tokn	*current;
	
	current = (*parser)->tab[TTHEAD];
	if (current)
	{
		append_token_tab((*parser)->tab, current, TTCURR);	
		if (parse_command_list(&current, *parser))
		{
			if (current)
				append_token_tab((*parser)->tab, current->next, TTNEXT);
			return (build_ast(parser));
		}
	}
	return (!(*parser)->tab[TTHEAD]);	
}
