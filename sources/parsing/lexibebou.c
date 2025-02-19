/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/19 15:30:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Move to utils -> remove static status
static void	consume_token(t_tokn **token)
{
	if (*token)
		*token = (*token)->next;
}

/*
//Parser state is a stack like int that increments each time the parser finds an
//OPAR. It decreases when encountering a CPAR, unless state = -1. If so, throws
//an error that stops the process (invalid syntax).
static void create_parsing_structure(t_pars *parser)
{
	parser->state = -1;
	parser->command_blocks = NULL;
}*/

//We use this function to split the original token list.*static bool	split_list(t_tokn *head, t_tokn *tail)
static bool	split_list(t_tokn **head, t_tokn **tail)
{
	t_tokn	*new_head;

	if (*head && *tail) // tail ? -> what if we reached the end of the list and tail is NULL ?
	{
		new_head = (*tail)->next;
		(*tail)->next = NULL;
		tail = head;
		*head = new_head;
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
bool	parse_script(t_bloc **list, t_tokn *tokens)
{
	//t_pars	parser;
	t_bloc		*tail;
    t_tokn		*current;

	tail = *list;
	current = tokens;
    (tokens) ? printf("%s	@	%s\n", tokens->value, __func__) : printf("End	@	%s\n", __func__);
    if (tokens)
	{
		if (parse_command_list(&current))
		{
			if (!is_state_active(current->type, OPAR))
			{
				create_command_node(list, &tail, tokens);
				split_list(&tokens, &current);
				if (tokens)
				{
					if (tokens->type == LORR || tokens->type == LAND) //LEAKS
																	  //Also, no split nor consumption
																	  //on subshell mode.
						consume_token(&tokens);
					if (tokens && current)
						return (parse_script(list, tokens));
				}
				return (true);
				//end of tokens (?)
			}
			else
			{
				while (tokens->type & OPAR)
				{
					if ((tokens->type & LORR || tokens->type & LAND || tokens->type & CPAR))
						consume_token(&current);
					else
						break;
				}
				return (parse_script(list, current));
			}
		}
		//Invalid parenthese.
	}
	return (false);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool	parse_command_list(t_tokn **current)
{
   // t_tokn *initial_node;

    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
   // initial_node = *current;
    if (*current)
	{
		if (parse_command(current))
		{
            if (*current)
			{
				if ((*current)->type == LAND || (*current)->type == LORR)
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
bool parse_command(t_tokn **current)
{
    //t_tokn	*initial_node;

    //initial_node = *current;
    (*current) ? printf("%s\t@\t%s\n", (*current)->value, __func__) : printf("End\t@\t%s\n", __func__);
    if (*current)
    {
        if ((*current)->type == OPAR)
        {
			consume_token(current);
            if (!parse_command_list(current))
			{
				printf("Syntax error: Expected token after '(' token.\n");
                return (false);
			}
			/*else if (!*current || (*current)->type != CPAR)
			{
				printf("Syntax error: Expected ')' token.\n");
				return (false);
			}*/
			if (*current)
			{
				consume_token(current);
				return (true);
			}
		//	*current = (*current)->next;
        //	return (true);
        }
        else if ((*current)->type != CPAR)
		{
			if (!parse_simple_command(current))
			{
				if ((*current) && (*current)->type != CPAR)
            		return (parse_pipeline(current));
			}
		}
		if (*current)
		{
			consume_token(current);
			return (true);
		}
     //   if (!*current || (*current)->type == CPAR)
       //     return (true);
        //*current = initial_node;
    }
	return (!*current || (*current)->type == CPAR);
    //return (false);
}

static bool	argument_or_redirection(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
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
	return (*current != NULL);
}

static bool	assignations(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
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

// Pipeline → Command ('|' Command)*
bool	parse_pipeline(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__); 
	if ((*current))
	{
		if ((*current)->type == PIPE)
		{
			consume_token(current);
			if (*current)
				return (parse_command(current)); 
			printf("Invalid syntax, expected token after PIPE token.\n");	
			return (false);
		}
		else if (has_next_elem(*current) && valid_lexeme(*current, OPAR, LORR))
			return (true);
	}
	//Pas sur de ce retour
	return (false);
}

// '(' CommandList ')'
bool	parse_compound_command(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == OPAR)
	{
		consume_token(current);
        parse_command_list(current);
		if ((*current)->type == CPAR)
		{
			consume_token(current);
            return (true);
        }
    }
    return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
bool	parse_assignment(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
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
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
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
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
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
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type & DOLL && (*current)->type < SQTE)
	{
		consume_token(current);
    	return (true);
	}
	return (parse_argument(current));
}
