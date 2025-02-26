#include "minislay.h"

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
