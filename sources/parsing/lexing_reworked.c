#include "minislay.h"

static void print_tokens(t_tokn *current)
{
	while (current)
	{
		printf("%s ", current->value);
		current = current->next;
	}
}

void	print_ast(t_tree *root)
{
	if (root)
	{

		printf("\n");

		while (root->tokens)
		{
			printf("%s ", root->tokens->value);
			root->tokens = root->tokens->next;
		}

		printf("\n");
		
		print_ast(root->left);
		
		print_ast(root->right);
	}
}

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
//v2
static void	delete_links(t_pars **parser)
{
	if (*parser && (*parser)->tab)
	{
		if ((*parser)->tab[TTPREV])
			(*parser)->tab[TTPREV]->next = NULL;
		if ((*parser)->tab[TTCURR])
			(*parser)->tab[TTCURR]->next = NULL;
	}
}*/

//

static void	delete_links(t_pars *parser)
{

	//
	//	Need futher refining
	//

	if (parser && parser->tab)
	{
		if (parser->tab[TTPREV])
			parser->tab[TTPREV]->next = NULL;
		if (parser->tab[TTCURR])
			parser->tab[TTCURR]->next = NULL;
	}
}

//
t_tree	*create_tree_node(t_tokn *tokens)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node)
	{
		print_tokens(tokens);
		new_node->tokens = tokens;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return (new_node);
}

/*
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
}*/

static bool	reset_token_tab(t_pars *parser, t_tokn *token, int token_index)
{
	int	index;

	if (parser && parser->tab)
	{
		index = 0;
		while (index < TTSIZE)
		{
			parser->tab[index] = NULL;
			if (index == token_index)
				parser->tab[index] = token;
			index++;	
		}
		return (true);
	}
	return (false);
//	return (parser && parser->tab);
}

//
bool	build_ast(t_tree **ast, t_pars	*parser)
{
	t_tokn	*save;

	if (ast)
		*ast = create_tree_node(parser->tab[TTCURR]);
	if (*ast)
	{	
		delete_links(parser);
		save = parser->tab[TTNEXT];
		(*ast)->tokens = parser->tab[TTCURR];
		reset_token_tab(parser, parser->tab[TTHEAD], TTHEAD);
		if (parse_script(&(*ast)->left, parser))
		{
			reset_token_tab(parser, save, TTHEAD);
			return (parse_script(&(*ast)->right, parser));
		}
	}
	print_ast(*ast);
	return (*ast);	
}

bool	parse_script(t_tree **ast, t_pars *parser)
{
	t_tokn	*current;
	
	current = parser->tab[TTHEAD];
	if (current)
	{
		append_token_tab(parser->tab, current, TTCURR);	
		if (parse_command_list(&current, parser))
		{	
			if (current)
				append_token_tab(parser->tab, current->next, TTNEXT);
			return (build_ast(ast, parser));
		}
	}
	return (!parser->tab[TTHEAD]);	
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

bool	parse_command_list(t_tokn **current, t_pars *parser)
{
	if (*current)
	{
		if (parse_command(current, parser))
		{
			if (*current)
			{
				if ((*current)->type & CPAR)
						
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

		
/* OLD
		if ((*current)->type == OPAR)
		{
			if (parse_compound_command(current, parser))
				return (set_state(&(parser)->state, CMPDCMD));
		}
		if (!parse_simple_command(current, parser))
			return (parse_pipeline(current, parser));
	}
	return (true);
}*/

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
