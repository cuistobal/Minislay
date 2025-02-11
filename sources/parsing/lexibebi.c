/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 18:44:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Main parsing function with backtracking
bool parse_script(t_tokn *tokens)
{
    t_tokn *current;

    current = tokens;
    (tokens) ? printf("%s	@	%s\n", tokens->value, __func__) : printf("End	@	%s\n", __func__);
    if (tokens)
		return (parse_command_list(&current));
	return (false);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool parse_command_list(t_tokn **current)
{
    t_tokn *initial_node;

    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    initial_node = *current;
    if (*current)
	{
        if (parse_command(current))
		{
            if (*current && ((*current)->type == LAND || (*current)->type == LORR))
			{
                *current = (*current)->next;
				if (*current)
					return (parse_command_list(current));
            }
            return (true);
        }
        *current = initial_node;
    }
    return (false);
}

bool	parse_command(t_tokn **current)
{
    t_tokn	*initial_node;
    bool	command_parsed;

    command_parsed = false;
    initial_node = *current;
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if (*current)
	{
		if ((*current)->type == OPAR)
    	    command_parsed = parse_compound_command(current);
    	else if (!parse_simple_command(current))
			command_parsed = parse_pipeline(current);
    	if (!*current)
			return (true);
		else
		{
			printf("%d\n", command_parsed);
			if ((*current)->type == LAND || (*current)->type == LORR)
				return (true);
		}
		if (!command_parsed)
    	    *current = initial_node;
	}
	return (command_parsed);
}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
bool	parse_simple_command(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
	if (*current)
	{
    	if ((*current)->type >= WORD && (*current)->type <= ARED)
		{
			if (parse_assignment(current))
			//	return (parse_simple_command(current));
			//	Since Assignement*	->	We should be calling parse_simple_command();
				return (parse_command(current));
			if ((*current)->type >= WORD && (*current)->type <= ARED)
			{
    	        //if ((*current)->type == WORD)
				//{
    	            //parse_argument(current);
				if (parse_argument(current))
    	            return (parse_simple_command(current));
//					return (parse_argument(current)); 
				return (parse_redirection(current));
//    	            return (parse_simple_command(current));
			}
				/*
				else
				{
					parse_redirection(current);
    	        	return (parse_simple_command(current));
				}*/
		}
		return ((*current)->type != PIPE);
    }
    return (false);
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if (parse_command(current))
	{
        if ((*current) && (*current)->type == PIPE)
		{
            *current = (*current)->next;
            return (parse_pipeline(current));
        }
        return (true);
    }
    return (false);
}

bool parse_compound_command(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);

    if ((*current)->type == OPAR)
	{
        *current = (*current)->next;
        if (parse_command_list(current))
        {
            if ((*current)->type == CPAR)
		    {
                *current = (*current)->next;
                return (true);
            }
        }
    }
    return (false);
}

// Assignment → WORD '=' Expression
bool parse_assignment(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);

    if (*current && (*current)->next)
	{
        if ((*current)->type == WORD && (*current)->next->type == EQUL)
		{
            *current = (*current)->next->next;
            return (parse_expression(current));
        }
    }
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == WORD)
	{
        *current = (*current)->next;
        return (true);
    }
    return (false);
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
bool	parse_redirection(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type >= IRED && (*current)->type <= ARED)
	{
        *current = (*current)->next;
        if ((*current)->type == WORD)
		{
            *current = (*current)->next;
            return (true);
        }
    }
    return (false);
}

// Edge case $ seul
// Expression → '$' WORD | WORD
bool	parse_expression(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == DOLL)
        *current = (*current)->next;
    return (parse_argument(current));
}

