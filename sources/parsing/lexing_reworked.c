#include "minislay.h"

static int	calls = 0;

/*
//Assesses if we're dealing with the last element of the list.
static bool	has_next_elem(t_tokn *current)
{
	if (current)
		return (current->next);
	return (false);
}*/

//Assesses if the lexeme's value falls within the set range 
static bool	valid_lexeme(t_tokn *current, int min, int max)
{
	return (current && (current->type >= min && current->type <= max));	
}

//This function saves the positions of current and sets it to ->next 
//
//We dont append the TTNEXT elemnt of the tab yet
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

//AST BUILDER

/*
//
static void	delete_links(t_tokn *current, t_tokn *prev)
{

	//
	//	Need futher refining
	//


	if (prev)
		
		prev->next = NULL;

	if (current)
		
		current->next = NULL;


}
*/

//
t_tree	*create_tree_node(t_tokn *tokens)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node)
	{
		new_node->tokens = tokens;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return (new_node);
}

static bool	build_right_side(t_tree **ast, t_tokn *tokens)
{
	t_tree	*new;
	t_tree	*save;

	if (!*ast)
	{
		new = create_tree_node(tokens);
		if (new)
			*ast = new;
		return (new);
	}
	else
	{
		save = (*ast)->right;
		new = create_tree_node(tokens);
		if (new)
		{
			(*ast)->right = new;
			new->left = save;
		}
	}
	return (new);
}

static bool	build_left_side(t_tree **ast, t_tokn *tokens)
{
	t_tree	*new;
	t_tree	*save;

	if (!*ast)
	{
		new = create_tree_node(tokens);
		if (new)
			*ast = new;
		return (new);
	}
	else
	{
		save = *ast;
		new = create_tree_node(tokens);
		if (new)
		{
			new->left = save;
			*ast = new;
		}
	}
	return (new);
}

//
bool	build_ast(t_tree **ast, t_pars *parser)
{
	if (ast)
		*ast = create_tree_node(parser->tab[TTCURR]);
	if (*ast)
	{
		(*ast)->tokens = parser->tab[TTCURR]
		//scenario ?
		(*ast)->right = create_tree_node(parser->tab[TTHEAD]);
		//scenario ?
		(*ast)->left = create_tree_node(parser->tab[TTNEXT]);
	}
	return (*ast);	
}


//
static void	print_tokens(t_tokn *start, t_tokn *end, int calls, char *msg)
{
	
	printf("\nPRINT TOKENS in %s	@	%d	->	\n", msg, calls);	

	while (start && start != end)
	{
		
		printf("%s ", start->value);	
		start = start->next;
	
	}
	printf("\n");
}


void	print_ast(t_tree *root)
{
	if (root)
	{

		while (root->tokens)
		{
			printf("%s ", root->tokens->value);
			root->tokens = root->tokens->next;
		}

		print_ast(root->left);
		
		print_ast(root->right);
	}
}

bool	parse_script(t_tokn *head, t_pars *parser)
//bool	parse_script(t_tokn *head)
{
	t_tokn	*current;
	
	current = head;
	
	append_token_tab(parser->tab, head, TTHEAD);
	
	while (current)
	{

		append_token_tab(parser->tab, current, TTCURR);
			
		if (parse_command_list(parser, &current))
		{
				
			if (current)
				
				append_token_tab(parser->tab, current->next, TTNEXT);

				
				//Silence the AST Warning
				//(*ast) ? printf("AST ISNT NULL\n") : printf("AST IS NULL\n");

			build_ast(parsing);
				
				//(*parser)->tokens = next;
				
				//	Build AST
				
				//
				
				//	Delete Links
			
		}

		append_token_tab(parser->tab, current, TTPREV);

		append_token_tab(parser->tab, parser->tab[TTNEXT], TTCURR);

		append_token_tab(parser->tab, NULL, TTNEXT);

		//current = next;			// This way we can keep track of the unparsed
								// part of the list.
	}
//	}
	return (current != head);
}

//
//	Il faut traverser l arbre en meme temps que la string && creer des branches
//	vers la gauche tant que l'on a pass rencontre le premier operateur le plus
//	significatif (PIPE | LAND | LORR)
//	Donc, tant qu'on est dans un sous-shell, on allour recursivement des noeuds
//	vers la gauche.
//

static bool	append_operator(t_tokn **operator, t_tokn **current, t_tokn **prev, t_pars *parser)
{
	if ((*current) && valid_lexeme(*current, LAND, LORR | OPAR))
	{
		*operator = *current;
		if (!(*current)->type & OPAR)
			parser->state & ROOTEDD;
		consume_token(current, prev);
		return (*current);
	}
	return (false);
}


/*
static bool	parse_next_branch(t_tree **ast, t_tokn **current, bool *rooted)
{
	if (*ast)
	{
		if (!*rooted)
	//		return (parse_command_list(&(*ast)->left, current, rooted)); //	(?)
	//	return (parse_command_list(&(*ast)->right, current, rooted)); //	(?)
			return (parse_command_list(ast, current, rooted)); //	(?)
		return (parse_command_list(ast, current, rooted)); //	(?)
	}
	return (parse_command_list(ast, current, rooted)); //	(?)
}
*/


bool	parse_command_list(t_tokn **current, t_tokn **prev, t_pars *parser)
//bool	parse_command_list(t_tokn **current)
{
	t_tokn		*save;			// For debug
	t_tokn		*operator;

	save = *current;			// For debug

	//print_tokens(save, NULL, calls, "ROOT");

	if (*current)
	{
		if (parse_command(current, parser))
		{
		
			calls++;

			print_tokens(save, *current, calls, "pcl	->	parse_command()");

			if ((*current) && ((*current)->type & CPAR))	// To be modified to avoid
															// the multitude of true returns
															// when in nested ()
				return (true);


			if (append_operator(current, parser))
			{
					
				(*prev) ? printf("PREV	->	%s\n", (*prev)->value) : printf("PREV IS NULL\n");
				(*current) ? printf("CURRENT	->	%s\n", (*current)->value) : printf("CURRENT IS NULL\n");
				(next) ? printf("NEXT	->	%s\n", next->value) : printf("NEXT IS NULL\n");

			}

			calls--;			
		
			return (true);

			//return (parse_next_branch(ast, current, rooted));
		}

	}
	
	return (!*current);
}

bool	parse_command(t_tokn **current, t_tokn **prev, t_pars *parser)
{
	if (*current)
	{
		if ((*current)->type == OPAR)
		{
			if (parse_compound_command(current, prev, parser))
				return (true);
		}
		if (!parse_simple_command(current, prev, parser))
			return (parse_pipeline(current, prev, parser));
	}
	return (true);
}

//We can return false -> It's the last sub funciton that aprse command goes
//Actually (?)
bool	parse_compound_command(t_tokn **current, t_tokn **prev, t_pars *parser)
{
	if ((*current)->type == OPAR)
	{
		set_state(&(parser)->state, SUBSHEL);
		consume_token(current, prev);
		if (parse_command_list(current, prev, parser))
		{
			if ((*current) && (*current)->type & CPAR)
				return (consume_token(current, prev));
		}
	}
	return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
// Finalement → EQUL 
bool	parse_assignment(t_tokn **current, t_tokn **prev, t_pars *parser)
{
    if ((*current) && (*current)->type & EQUL)
		return (consume_token(current, prev));
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current, t_tokn **prev, t_pars *parser)
{
    if ((*current) && (*current)->type & WORD)
		return (consume_token(current, prev));
	return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current, t_tokn **prev, t_pars *parser)
{
	if (*current)
	{
    	if ((*current)->type >= IRED && (*current)->type <= (ARED | OPAR))
		{

			consume_token(current, prev);
    	    
			if ((*current))
			{
				
				if ((*current)->type & WORD)
				
					return (consume_token(current, prev));
				
				printf("syntax error: Unexpected %s token after %s token.\n", (*current)->value, (*prev)->value);
				
				return (false);
			
			}
			
			*current = *prev;
			
			printf("syntax error: Unexpected EOF token after %s token.\n", (*prev)->value);
    	
		}
	
	}
    
	//return (false);
    
	return (!*current);
}

// Edge case $ seul + gerer 
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current, t_tokn **prev)
{
    if ((*current)->type & DOLL && (*current)->type < SQTE)
		
		return (consume_token(current, prev));
	
	return (parse_argument(current, prev));
}

static bool	argument_or_redirection(t_tokn **current, t_tokn **prev)
{
	if (*current)
	{
		if (!parse_redirection(current, prev))
		{
			if (parse_argument(current, prev))
				return (argument_or_redirection(current, prev));
			return (false);
		}
		return (argument_or_redirection(current, prev));
	}
	return (!*current);
}

static bool	assignations(t_tokn **current, t_tokn **prev)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (current)
	{
		if (parse_assignment(current, prev))
			return (assignations(current, prev));
		return (false);
	}
	return (!*current);

}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
// The WORD element in the middle is not mandatory.
bool	parse_simple_command(t_tokn **current, t_tokn **prev)
{
	if (*current)
	{
		assignations(current, prev);
		return (argument_or_redirection(current, prev));
    }
	return (!*current);
}

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current, t_tokn **prev, t_pars *parser)
{
	if (*current)
	{

		if ((*current)->type & PIPE)	
		{

			consume_token(current, prev);
			
			if (*current)

				return (parse_command(current, prev, parser)); 
			
			printf("Invalid syntax, expected token after PIPE token.\n");	
			
			return (false);
		
		}

        return (true); //A retravailler

	}

	return (!*current);

}
