/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:43:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 12:52:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Function prototypes
bool parse_script(t_tokn *tokens, int *index);
bool parse_command_list(t_tokn *tokens, int *index);
bool parse_command(t_tokn *tokens, int *index);
void parse_simple_command(t_tokn *tokens, int *index);
void parse_pipeline(t_tokn *tokens, int *index);
void parse_compound_command(t_tokn *tokens, int *index);
void parse_assignment(t_tokn *tokens, int *index);
void parse_argument(t_tokn *tokens, int *index);
void parse_redirection(t_tokn *tokens, int *index);
void parse_expression(t_tokn *tokens, int *index);

// Main parsing function with backtracking
bool parse_script(t_tokn *tokens, int *index)
{
    //int initial_index = *index;
    
	if (parse_command_list(tokens, index))
        return true;
   // *index = initial_index; // Restore state on failure
    return false; // Failure
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool parse_command_list(t_tokn *tokens, int *index)
{
	int op_index;
    int initial_index;

	initial_index = *index;
    if (parse_command(tokens, index))
	{
        while (tokens[*index].type == LAND || tokens[*index].type == LORR)
		{
            op_index = *index;
            (*index)++;
            if (!parse_command_list(tokens, index))
			{
                *index = op_index;
				return (false);
            }
        }
        return (true);
    }
    *index = initial_index;
	return (false);
}

// Command → SimpleCommand | Pipeline | CompoundCommand
bool parse_command(t_tokn *tokens, int *index)
{
    int initial_index;
    
	initial_index = *index;
    if (tokens[*index].type == WORD)
	{
        parse_simple_command(tokens, index);
        return (true);
    }
	else if (tokens[*index].type == PIPE)
	{
        parse_pipeline(tokens, index);
        return (true);
    }
	else if (tokens[*index].type == OPAR)
	{
        parse_compound_command(tokens, index);
        return (true);
    }
    *index = initial_index; // Restore state on failure
    return (false);
}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
void parse_simple_command(t_tokn *tokens, int *index)
{
    while (tokens[*index].type == WORD && tokens[*index + 1].type == EQUL)
        parse_assignment(tokens, index);
    if (tokens[*index].type == WORD)
        (*index)++;
    while (tokens[*index].type == WORD || tokens[*index].type == IRED ||
           tokens[*index].type == ORED || tokens[*index].type == HDOC ||
           tokens[*index].type == ARED)
	{
        if (tokens[*index].type == WORD)
            parse_argument(tokens, index);
		else
			parse_redirection(tokens, index);
    }
}

// Pipeline → Command ('|' Command)*
void parse_pipeline(t_tokn *tokens, int *index)
{
    parse_command(tokens, index);
    while (tokens[*index].type == PIPE)
	{
        (*index)++;
        parse_command(tokens, index);
    }
}

// CompoundCommand → '(' CommandList ')'
void parse_compound_command(t_tokn *tokens, int *index)
{
    if (tokens[*index].type == OPAR)
	{
        (*index)++;
        parse_command_list(tokens, index);
        if (tokens[*index].type == CPAR)
            (*index)++;
    }
}

// Assignment → WORD '=' Expression
void parse_assignment(t_tokn *tokens, int *index)
{
    if (tokens[*index].type == WORD && tokens[*index + 1].type == EQUL)
	{
        (*index)++;
		(*index)++;
		parse_expression(tokens, index);
    }
}

// Argument → WORD
void parse_argument(t_tokn *tokens, int *index)
{
    if (tokens[*index].type == WORD)
		(*index)++;
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
void parse_redirection(t_tokn *tokens, int *index)
{
    if (tokens[*index].type == IRED || tokens[*index].type == ORED ||
        tokens[*index].type == HDOC || tokens[*index].type == ARED)
	{
        (*index)++;
        if (tokens[*index].type == WORD)
			(*index)++;
    }
}

// Expression → '$' WORD | WORD
void parse_expression(t_tokn *tokens, int *index)
{
    if (tokens[*index].type == DOLL)
	{
        (*index)++;
        if (tokens[*index].type == WORD)
            (*index)++;
    }
	else if (tokens[*index].type == WORD)
        (*index)++;
}

