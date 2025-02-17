/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/17 11:51:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Main parsing function with backtracking
bool parse_script(t_tokn *tokens)
{
    t_tokn *current;
    t_tokn *initial_node;

    current = tokens;
    initial_node = current;
    (tokens) ? printf("%s	@	%s\n", tokens->value, __func__) : printf("End	@	%s\n", __func__);
    if (tokens)
	{
		if (parse_command_list(&current))
    	    return (true);
    	current = initial_node;
	}
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
            if (*current)
			{
				if ((*current)->type == LAND || (*current)->type == LORR)
				{
                	*current = (*current)->next;
					if (!*current)
						return (false);
				}
				return (parse_command_list(current));
            }
            return (true);
        }
        *current = initial_node;
    }
    return (*current == NULL);
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
    	    return (parse_compound_command(current));
    	else if (!parse_simple_command(current))
			return (parse_pipeline(current));
    	if (!*current || (*current)->type == CPAR)
			return (true);
		else
		{
			printf("%d	->	%s\n", command_parsed, (*current)->value);
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
				return (parse_simple_command(current));
    	    if ((*current)->type >= WORD && (*current)->type <= ARED)
			{
    	        if ((*current)->type & WORD)
				{
    	            parse_argument(current);
    	            return (parse_simple_command(current));
				}
				else
				{
					parse_redirection(current);
    	        	return (parse_simple_command(current));
				}
    	    }
			return (true);
		}
    }
    return (*current == NULL);
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == PIPE)
	{
		*current = (*current)->next;
		return (parse_command(current)); 
	}
    return (false);
}

// '(' CommandList ')'
bool parse_compound_command(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type == OPAR)
	{
        *current = (*current)->next;
        parse_command_list(current);
        if ((*current)->type == CPAR)
		{
            *current = (*current)->next;
            return (true);
        }
    }
    return (false);
}

// Assignment → WORD '=' Expression -> Implemtanton a revoir
bool parse_assignment(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);

    if (*current && (*current)->next)
	{
        if ((*current)->type & WORD && (*current)->next->type == EQUL)
		{
            *current = (*current)->next->next;
            parse_expression(current);
        }
    }
    return (false);
}

// Argument → WORD
bool	parse_argument(t_tokn **current)
{
    (*current) ? printf("%s	@	%s\n", (*current)->value, __func__) : printf("End	@	%s\n", __func__);
    if ((*current)->type & WORD)
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
        if ((*current)->type & WORD)
		{
            *current = (*current)->next;
            return (true);
        }
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
        *current = (*current)->next;
    	return (true);
	}
	return (parse_argument(current));
}
