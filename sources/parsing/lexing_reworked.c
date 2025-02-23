#include "minislay.h"

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

bool	consume_token(t_tokn **current)
{
	if (*current)
	{
		*current = (*current)->next;
		return (true);
	}
	return (false);
}

//AST BUILDER

static void	delete_links(t_tokn *tokens, t_tokn *current)
{
	while (tokens)
	{
		if ((tokens)->next == current)
			(tokens)->next = NULL;
		tokens = (tokens)->next;	
	}
	if (current)
		(current)->next = NULL;
}

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

bool	build_ast(t_tree **ast, t_tokn *tokens, t_tokn *current)
{
	t_tokn	*next;

	if (current)
	{
		if (!*ast)
			*ast = create_tree_node(current);
		if (*ast)
		{
			next = current->next;
			(*ast)->right = create_tree_node(next);
			if ((*ast)->right)
			{
				(*ast)->left = create_tree_node(tokens);
				if ((*ast)->left)
					delete_links(tokens, current);
				return ((*ast)->left);
			}
			return ((*ast)->right);
		}
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



bool	parse_script(t_tree **ast, t_tokn *head)
//bool	parse_script(t_tokn *head)
{
	t_tree	*root;
	t_tokn	*current;

	root = *ast;
	current = head;
	if (current)
	{
		if (!parse_command_list(ast, &current))
			printf("%s	&&	%d\n", current->value, current->type);
		//return (parse_command_list(&current));
		print_ast(root);
	}
	return (current != head);
}

static int	calls = 0;

//
//	Il faut traverser l arbre en meme temps que la string && creer des branches
//	vers la gauche tant que l'on a pass rencontre le premier operateur le plus
//	significatif (PIPE | LAND | LORR)
//	Donc, tant qu'on est dans un sous-shell, on allour recursivement des noeuds
//	vers la gauche.
//

//0	- ROOT
//1	- LEFT
//2	- RIGHT
static bool	build_tree(t_tree **ast, t_tokn *save, t_tokn *current)
{
	t_tree	*new_branch;

	if (current)
	{
		if (!*ast)
			*ast = create_tree_node(NULL);
		if (*ast)
		{
			if ((*current)->next)
			{

			}
			else
			{
				(*ast)->right = create_tree_node();
				return ((*ast)->right);
			}
		}
		return (*ast); //if !(*ast)	->	malloc failed
	}
	return (save);
	//return (save == current);	->	Fin de l arbre, les 2 sont nuls
}

bool	parse_command_list(t_tree **ast, t_tokn **current)
//bool	parse_command_list(t_tokn **current)
{
	t_tokn	*save;
	t_tokn	*operator;

	save = *current;
	
	//print_tokens(save, NULL, calls, "ROOT");

	if (*current)
	{
		if (parse_command(current))
		{
		
			//print_tokens(save, *current, calls, "BRANCH");
		
			calls++;

			build_ast(ast, save, *current); // (*current)->next ? 	->	build on left
									   		// else					->	build on root

			//Creer un noeud left
			printf("\nCREATE LEFT NODE");
			print_tokens(save, *current, calls, "BRANCH");


			if ((*current) && ((*current)->type & CPAR))
				return (true);
			if ((*current) && valid_lexeme(*current, LAND, LORR | OPAR))
			//		((*current)->type & LORR || (*current)->type & LAND))
			{
				printf("\nCREATE ROOT NODE");
				printf("\n%s\n", (*current)->value);	
				
				//Retour sur la root
				//Loger l operateur logique
				operator = *current;
				consume_token(current);

				if (*current)
					//Creer un noeud droite
					//Loger le reste de l'expression
				
				printf("\nCREATE RIGHT NODE");
				print_tokens(*current, NULL, calls, "");
					
				/*Impossible to get there since consume_token() can dereference
					 * current->next.
					 * We could get a LORR | LAND without a following command
					 * OR
					 * We could get a LORR | LAND with a following CPAR
					 *
					 * Both situations terrifies me.
					 * Joke apart, we need to secure those scenarios
					 */
			}
			calls--;
			//return (parse_command_list(current));
			return (parse_command_list(&(*ast)->right, current)); //	(?)
		}
	//	return (*current);
	/* It possibly makes more sense building the left side node after the right
	 * side node. Hence, we'de remove the upper call to the create_ast_node()
	 * function.
	 */
	//	return (create_ast_node(ast, *current, save));
	//	OR
	//	return (create_ast_node(&(*ast)->left, *current, save));
	}
	//	Edge case	->	current is NULL && different from save -> means that
	//	parse_command() failed.
	return (!*current);
}

bool	parse_command(t_tokn **current)
{
	t_tokn *save;

	save = *current;
	if (*current)
	{
		if ((*current)->type == OPAR)
		{
			if (parse_compound_command(current))
				return (true);
			*current = save;
		}
		if (!parse_simple_command(current))
			return (parse_pipeline(current));
	}
	return (true);
}

//We can return false -> It's the last sub funciton that aprse command goes
//Actually (?)
bool	parse_compound_command(t_tokn **current)
{
	if ((*current)->type == OPAR)
	{
		consume_token(current);
		if (parse_command_list(current))
		{
			if ((*current)->type & CPAR)
				return (consume_token(current));
		}
	}
	return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
// Finalement → EQUL 
bool	parse_assignment(t_tokn **current)
{
    if ((*current) && (*current)->type & EQUL)
		return (consume_token(current));
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current)
{
    if ((*current) && (*current)->type & WORD)
		return (consume_token(current));
	return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current)
{
	t_tokn	*save;

	save = NULL;
	if (*current)
	{
    	if ((*current)->type >= IRED && (*current)->type <= (ARED | OPAR))
		{
			save = *current;
			consume_token(current);
    	    if ((*current))
			{
				if ((*current)->type & WORD)
					return (consume_token(current));
				printf("syntax error: Unexpected %s token after %s token.\n", (*current)->value, save->value);
				return (false);
			}
			*current = save;
			printf("syntax error: Unexpected EOF token after %s token.\n", save->value);
    	}
	}
    //return (false);
    return (!*current);
}

// Edge case $ seul + gerer 
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current)
{
    if ((*current)->type & DOLL && (*current)->type < SQTE)
		return (consume_token(current));
	return (parse_argument(current));
}

static bool	argument_or_redirection(t_tokn **current)
{
	if (*current)
	{
		if (!parse_redirection(current))
		{
			if (parse_argument(current))
				return (argument_or_redirection(current));
			return (false);
		}
		return (argument_or_redirection(current));
	}
	return (!*current);
}

static bool	assignations(t_tokn **current)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (current)
	{
		if (parse_assignment(current))
			return (assignations(current));
		return (false);
	}
	return (!*current);

}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
// The WORD element in the middle is not mandatory.
bool	parse_simple_command(t_tokn **current)
{
	if (*current)
	{
		assignations(current);
		return (argument_or_redirection(current));
    }
	return (!*current);
}

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current)
{
	if (*current)
	{
		if ((*current)->type & PIPE)
		{
			consume_token(current);
			if (*current)
				return (parse_command(current)); 
			printf("Invalid syntax, expected token after PIPE token.\n");	
			return (false);
		}
		/*
		else if ((*current)->type & OPAR || (*current)->type & CPAR)
		{
			if (valid_lexeme(*current, LAND, LORR | OPAR))
            {
				consume_token(current);
                if (has_next_elem(*current))
				    return (parse_command(current));
            } 
            *//*
			if (has_next_elem(*current) && valid_lexeme(*current, LAND, LORR | OPAR))
			{
				consume_token(current);
				return (parse_command(current));
			}
			else if ((*current)->type == CPAR)
			    return (consume_token(current));
            
				if (*current && (*current)->type > (LORR | OPAR))
					return (parse_command(current));
		        //return (valid_lexeme(*current, WORD, LORR | OPAR));
			}
            printf("%s\n", (*current)->value);*/
            return (true); //A retravailler
//		}
//		return (valid_lexeme(*current, WORD, SQTE | OPAR));
	}
	return (!*current);
}
