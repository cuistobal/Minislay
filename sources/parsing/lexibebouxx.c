/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/12 10:13:56 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Main parsing function with backtracking
bool	parse_script(t_tokn *tokens)
{
    t_tokn	*current;

    current = tokens;
    (tokens) ? printf("%s	@	%s\n", tokens->value, __func__) : printf("End	@	%s\n", __func__);
    if (tokens)
		return (parse_command_list(&current));
	return (false);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool	parse_command_list(t_tokn **current)
{
    t_tokn	*initial_node;

    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    initial_node = *current;
    if (*current)
	{
        if (parse_command(current))
		{
            while (*current && ((*current)->type == LAND || (*current)->type == LORR))
			{
                *current = (*current)->next;
				return (parse_command(current));
            }
            return (true);
        }
        *current = initial_node;
    }
    return (false);
}

// Do we have a simple command or a compound command ?
// Do we have a pipeline ?
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
		//	printf("%d\n", command_parsed);
			//if ((*current)->type == LAND || (*current)->type == LORR)
			//	return (true);
			return ((*current)->type < PIPE && (*current)->type > LORR);
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
    	while ((*current)->type == WORD && (*current)->next && (*current)->next->type == EQUL)
		{
			if (!parse_assignment(current))
				return (false);
		}
		if ((*current)->type == WORD)
		{
			*current = (*current)->next;
			while ((*current) && ((*current)->type >= WORD && (*current)->type <= ARED))
			{
				if ((*current)->type == WORD)
					return (parse_argument(current));
				return (parse_redirection(current));
				/*
				if ((*current)->type == WORD)
				{
					if (!parse_argument(current))
						return (false);
				}
				else
				{
					if (!parse_redirection(current))
						return (false);
				}
				if (!*current)
					break;
			*/
			}
			return (true);
		}
		return (false);
    }
    return (false);
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if (parse_command(current))
	{
        while ((*current) && (*current)->type == PIPE)
		{
            *current = (*current)->next;
            if (!parse_simple_command(current))
                return (false);
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
	//printf("%s\n", (*current)->value);
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

