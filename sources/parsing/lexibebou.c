/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/24 14:39:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
//	TESTS
//

static void	print_tokens(t_tokn *tokens)
{
	printf("PRINT TOKENS	->	");
	while (tokens)
	{
		printf("%s ", tokens->value);
		tokens = tokens->next;
	}
	printf("\n");
}

/*
static void	print_ast(t_tree *ast)
{
	if (ast)
	{
		printf("PRINT AST 	->	");
		while (ast->tokens)
		{
			printf("%s ", ast->tokens->value);
			ast->tokens = ast->tokens->next;
		}
		printf("\n");
		printf("left node\n");
		print_ast(ast->left);
		printf("right node\n");
		print_ast(ast->right);
		return ;
	}
	//printf("le vide lo\n");
}*/

//
//	UTILS
//


//Assesses if we're dealing with the last element of the list.
static bool	has_next_elem(t_tokn *current)
{
	if (current)
		return (current->next);
	return (false);
}

//Assesses if the lexeme's value falls within the set range 
static bool	valid_lexeme(t_tokn *current, int min, int max)
{
	return (current && (current->type >= min && current->type <= max));	
}



//
//	ALGO
//

static void	delete_links(t_tokn *tokens, t_tokn *current)
{
	while (tokens)
	{
	//	printf("%s ", (tokens)->value);
		if ((tokens)->next == current)
			(tokens)->next = NULL;
		tokens = (tokens)->next;	
	}
//	printf("\n");
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

	//printf("JE CONSTRUIT DES ABRES OUAIS OUAIS OUAIS\n");
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

/*
static void	print_command(t_tokn *command, t_tokn *limit)
{
	printf("\n\nCOMAND	LIST:\n\n");
	while (command && command != limit)
	{
		printf("%s	&&	%d\n", command->value, command->type);
		command = command->next;
	}
	printf("\n\nEND	OF	LIST:\n\n");
}*/

bool	parse_script(t_tree	**ast, t_tokn *tokens)
{
//	t_tokn			*next;
	t_tokn			*current;

	//next = NULL;
	current = tokens;

//	print_ast(ast);

	if (current && parse_command_list(&current))
	{
		//current ? printf("		Sucessfully parsed tokens from { %s && %d } to { %s && %d }\n", tokens->value, tokens->type, current->value, current->type) : printf("			Last command starts at { %s && %d }\n", tokens->value, tokens->type);
		if (current)
		{
			print_tokens(current);
			//print_command(tokens, current);
			if (current->type & LORR || current->type & LAND || current->type & CPAR)
			{	
				consume_token(&current);
				while (current->type & CPAR)
					consume_token(&current);
			}
			return (parse_script(ast, current));	

//		AST MODULE CODE

				//printf("%s	IN	%s\n", current->value, __func__);
				//print_command(tokens, current);
	/*			if (!(current->type & CPAR))
				{
					next = current->next;

					if (build_ast(ast, current, tokens))
					{
						//ast->left ? (ast->right ? printf("BOTH OK\n") : printf("LEFT OK\n")) : (ast->right ? printf("RIGHT OK\n") : printf("BOTH KO\n"));
						if (parse_script(&(*ast)->left, tokens))
							return (parse_script(&(*ast)->right, next));
					}
					//{
						//tokens ? printf("After build AST				%s\n", tokens->value) :printf("After delete links			TOKENS IS NULL\n");
						

						//next = current->next;
						//delete_links(tokens, current);
						//if (parse_script(ast->left, tokens))
						//if (parse_script(&(*ast)->right, current->next))
						//{
							//tokens ? printf("After parse right			%s\n", tokens->value) : printf("After delete links			TOKENS IS NULL\n");
							//print_tokens(tokens);
							//delete_links(tokens, current);
							//print_tokens(tokens);
							//tokens ? printf("After delete links			%s\n", tokens->value) : printf("After delete links			TOKENS IS NULL\n");
						//	print_ast(ast);
						//	return (parse_script(ast->right, next));
							//return (parse_script(&(*ast)->left, tokens));
						//}
					//}
					//return (false);
				}
				consume_token(&current);
				*/

//		AST MODULE CODE ENDS


			}
			//current ? printf("Sending %s back to Irak\n", current->value) : printf("NULL\n");
			return (parse_script(ast, current));
		}
		return (true);
	//}
///	return (true);
}

/*
//We use this function to split the original token list.*static bool	split_list(t_tokn *head, t_tokn *tail)
static bool	split_list(t_tokn **token, t_tokn **current, t_tokn **save)
{
	t_tokn	*new_head;

	if (*token) // tail ? -> what if we reached the end of the list and tail is NULL ?
	{
		if (*current)
		{
			new_head = (*current)->next;
			(*current)->next = NULL;
			*current = *token;
			*token = *save;
			*save = new_head;
		}
	}
	return (true); //Need to work on that return
}

//Appending the sub token_list to the global command_list
static bool create_command_node(t_bloc **list, t_bloc **tail, t_tokn *tokens)
{
	t_bloc	*new_node;

	new_node = (t_bloc *)malloc(sizeof(t_bloc));
	if (new_node)
	{
		new_node->token = tokens;
		new_node->next = NULL;
		if (!*list)
		{
			*list = new_node;
			*tail = new_node;
		}
		else
		{
			(*tail)->next = new_node;
			*tail = new_node;	
		}
	}
	return (new_node);
}

// Main parsing function with backtracking
// We need to add a module that creates a copy of the meaningfull main list
// elements and build the AST out of it OR build the AST straight away.
bool	parse_script(t_bloc **list, t_tokn *tokens, t_tokn *save)
{
	t_bloc			*tail;
    t_tokn			*current;

	tail = *list;
	current = tokens;
    (tokens) ? printf("%s	@	%s\n", tokens->value, __func__) : printf("End	@	%s\n", __func__);
    if (tokens)
	{
		if (save != tokens && !is_state_active(current->type, OPAR))
		{
			printf("I'm here	%s\n", tokens->value);
			create_command_node(list, &tail, tokens);
			split_list(&tokens, &current, &save);
			if (tokens)
			{
				if (tokens->type == LORR || tokens->type == LAND)
					consume_token(&tokens);
				if (tokens && save)
					return (parse_script(&tail, tokens, save));
			}
		}
		//	printf("		%s\n", tokens->value);
		if (parse_command_list(&current))
		{
			current ? printf("Post parse_command()	->	%s	&&	%d\n", current->value, current->type) : printf("\n");
			if (current && !is_state_active(current->type, OPAR))
			{
				create_command_node(list, &tail, tokens);
				split_list(&tokens, &current, &save);
				if (tokens)
				{
					if (tokens->type == LORR || tokens->type == LAND)
						consume_token(&tokens);
					if (tokens && save)
						return (parse_script(&tail, tokens, save));
				}
				return (true);
				//end of tokens (?)
			}
			else if (current)
			{
				if (current && current->type & OPAR)
				{
					while (current && (current->type & LORR || current->type & LAND || current->type & CPAR))
						consume_token(&current);
				}
				return (parse_script(list, current, save));
			}
			return (true);
		}
		//Invalid parenthese.
	}
	return (*list);
}*/

// CommandList → Command ('&&' | '||') CommandList | Command
bool	parse_command_list(t_tokn **current)
{
   // t_tokn *initial_node;

    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
   // initial_node = *current;
    if (*current)
	{
		if ((*current)->type == OPAR)
			return (parse_compound_command(current));
		else if (parse_command(current))
		{
            if (*current)
			{
				//if ((*current)->type == LAND || (*current)->type == LORR)
				if ((*current)->type & LAND || (*current)->type & LORR)
				{
                	//*current = (*current)->next;
				//	if (!*current)
				//		return (false);
					return ((*current)->next);
				//	return (parse_command_list(current));
				}
				return (true);
			//	printf("Je n'ai rien a faire ici.\n");
			//	return (parse_command_list(current));
            }
            return (true);
        }
       // *current = initial_node;
    }
    return (*current == NULL);
}

//TEST
// Command → CompoundCommand | SimpleCommand | Pipeline
bool	parse_command(t_tokn **current, t_tokn **prev, bool *rooted, int *subshells)
{
    if (*current)
    {

        if ((*current)->type == OPAR)
        {

			consume_token(current, prev);

			if (!parse_compound_command(current, prev, rooted, subshells))
			{
				printf("Syntax error: Expected token after '(' token.\n");
                return (false);
			}

			if (*current)
			{

				return (consume_token(current, prev));

			}

        }

        else if ((*current)->type != CPAR)
		{

			if (!parse_simple_command(current))
			{
				if ((*current) && (*current)->type != CPAR)
            		return (parse_pipeline(current));
			}
		}/*
		if (*current)
		{
			consume_token(current);
			return (true);
		}*/
     //   if (!*current || (*current)->type == CPAR)
       //     return (true);
        //*current = initial_node;
    }
	return (!*current || (*current)->type == CPAR);
    //return (false);
}

static bool	argument_or_redirection(t_tokn **current)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (*current)
	{
		if (!parse_redirection(current))
		{
			if (parse_argument(current))
				return (argument_or_redirection(current));
			return (false);
		}
//		printf("Problematic token		->		");
//    	(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
		return (argument_or_redirection(current));
	}
	return (*current != NULL);
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
	return (*current != NULL);

}

//Separer en 3 fonctions	->	ASSIGNATIONS | XXX | (ARGUMENT | REDIRECTIONS)
// SimpleCommand → Assignment* WORD (Argument | Redirection)*
bool	parse_simple_command(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (*current)
	{
		assignations(current);
		return (argument_or_redirection(current));
	/*	if (parse_argument(current))
		{
			if (*current)
				return (argument_or_redirection(current));
		}*/
		/*
			//Boucle 2
    	//	while ((*current)->type >= WORD && (*current)->type <= ARED)//A modifier pour tenir compte du state parentheses.
		//	{
			//	if ((*current)->type & WORD)
			//		parse_argument(current);
			//	else
			//		parse_redirection(current);
    	    if ((*current) && (parse_argument(current) || parse_redirection(current))) //mettre parse redirection en 1er ?
			{
				while ((*current) && (parse_argument(current) || parse_redirection(current)))
				{
				}
			}
		}*/
    }
    return (*current == NULL);
}

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__); 
	if ((*current))
	{
		if ((*current)->type & PIPE)
		{
			consume_token(current);
			if (*current)
				return (parse_command(current)); 
			printf("Invalid syntax, expected token after PIPE token.\n");	
			return (false);
		}
		return (has_next_elem(*current) && valid_lexeme(*current, OPAR, LORR)); //LORR + OPAR btw
//		else if (has_next_elem(*current) && valid_lexeme(*current, OPAR, LORR))
	//	{
	//		printf("%s\n", (*current)->value);
			//if ((*current)->type & CPAR)
				//printf("%s	->	%d	@	%s\n", (*current)->value, (*current)->type, __func__);
				//consume_token(current);
	//		return (true);
	//	}
	}
	//Pas sur de ce retour
	return (false);
}

// '(' CommandList ')'
bool	parse_compound_command(t_tokn **current, t_tokn **prev, bool *rooted, int *subshells)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == OPAR)
	{
		consume_token(current, prev);
        parse_command_list(current, prev, rooted, subshells);
		if ((*current)->type & CPAR)
		{
			consume_token(current, prev);
            return (true);
        }
    }
    return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
bool	parse_assignment(t_tokn **current)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current) && (*current)->type & EQUL)
	{
		consume_token(current);
		return (true);
	}
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current) && (*current)->type & WORD)
	{
		consume_token(current);	
        return (true);
    }
    return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current)
{
	t_tokn	*save;

	save = NULL;
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type >= IRED && (*current)->type <= ARED)
	{
		save = *current;
		consume_token(current);
        if ((*current))
		{
			if ((*current)->type & WORD)
			{
				consume_token(current);
        	    return (true);
        	}
			printf("syntax error: Unexpected %s token after %s token.\n", (*current)->value, save->value);
		}
		*current = save;
		//Syntax error	->	Expected "" token after REDIRECTION -> FOUND EOF INSTEAD
    }
    return (false);
}

// Edge case $ seul + gerer 
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current)
{
    //(*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type & DOLL && (*current)->type < SQTE)
	{
		consume_token(current);
    	return (true);
	}
	return (parse_argument(current));
}
