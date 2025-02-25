#include "minislay.h"

//
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
			{
				append_token_tab((*parser)->tab, current->next, TTNEXT);
				return (build_ast(parser));
			}
			return (true);
		}
	}
	return (!(*parser)->tab[TTHEAD]);	
}


//
//	Il faut traverser l arbre en meme temps que la string && creer des branches
//	vers la gauche tant que l'on a pass rencontre le premier operateur le plus
//	significatif (PIPE | LAND | LORR)
//	Donc, tant qu'on est dans un sous-shell, on allour recursivement des noeuds
//	vers la gauche.
//
static bool	append_operator(t_tokn **current, t_pars *parser)
{
	if ((*current) && valid_lexeme(*current, LAND, LORR | OPAR))
	{
		if (!(*current)->type & OPAR)
			set_state(&parser->state, ROOTEDD);
		return ((*current)->next);
	}
	return (*current);
}

//
bool	parse_command_list(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (parse_command(current, parser))
		{
			if (*current)
			{
				//if ((*current)->type & CPAR)

				return (append_operator(current, parser));
			}
		}
	
		//		return (true);

		//If there is an operator -> end of the command block with CMPD CMND status
		//
		//ELse
		//
		//	Simple command | PIpeline
		
	}
	return (!*current);
}

//
bool	parse_command(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (!parse_compound_command(current, parser))
		{
			if (!parse_simple_command(current, parser))
				return (parse_pipeline(current, parser));
		}
	}
	return (!*current);
}

//We can return false -> It's the last sub funciton that aprse command goes
//Actually (?)
bool	parse_compound_command(t_tokn **current, t_pars *parser)
{
	if ((*current)->type == OPAR)
	{
		set_state(&(parser)->state, SUBSHEL);
		consume_token(current, parser);
		if (parse_command_list(current, parser))
		{
			if ((*current) && (*current)->type & CPAR)
				return (consume_token(current, parser));
		}
	}
	return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
// Finalement → EQUL 
bool	parse_assignment(t_tokn **current, t_pars *parser)
{
    if ((*current) && (*current)->type & EQUL)
		return (consume_token(current, parser));
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current, t_pars *parser)
{
    if ((*current) && (*current)->type & WORD)
		return (consume_token(current, parser));
	return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
    	if ((*current)->type >= IRED && (*current)->type <= (ARED | OPAR))
		{

			consume_token(current, parser);
    	    
			if ((*current))
			{
				
				if ((*current)->type & WORD)
				
					return (consume_token(current, parser));
				
				printf("syntax error: Unexpected %s token after %s token.\n", (*current)->value, (parser)->tab[TTPREV]->value);
				
				return (false);
			
			}
			
			*current = (parser)->tab[TTPREV];
			
			printf("syntax error: Unexpected EOF token after %s token.\n", (*current)->value);
    	
		}
	
	}
    
	//return (false);
    
	return (!*current);
}

// Edge case $ seul + gerer 
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current, t_pars *parser)
{
    if ((*current)->type & DOLL && (*current)->type < SQTE)
		
		return (consume_token(current, parser));
	
	return (parse_argument(current, parser));
}

static bool	argument_or_redirection(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (!parse_redirection(current, parser))
		{
			if (parse_argument(current, parser))
				return (argument_or_redirection(current, parser));
			return (false);
		}
		return (argument_or_redirection(current, parser));
	}
	return (!*current);
}

static bool	assignations(t_tokn **current, t_pars *parser)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (current)
	{
		if (parse_assignment(current, parser))
			return (assignations(current, parser));
		return (false);
	}
	return (!*current);

}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
// The WORD element in the middle is not mandatory.
bool	parse_simple_command(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		assignations(current, parser);
		return (argument_or_redirection(current, parser));
    }
	return (!*current);
}

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current, t_pars *parser)
{
	if (*current)
	{

		if ((*current)->type & PIPE)	
		{

			set_state(&parser->state, PIPELIN);

			consume_token(current, parser);
			
			if (*current)

				return (parse_command(current, parser)); 
			
			printf("Invalid syntax, expected token after PIPE token.\n");	
			
			return (false);
		
		}

        return (true); //A retravailler

	}

	return (!*current);

}
