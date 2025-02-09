/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:51:47 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/09 12:03:45 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool parse_script(t_tokn **current);
bool parse_command_list(t_tokn **current);
bool parse_command(t_tokn **current);
bool parse_simple_command(t_tokn **current);
bool parse_assignment(t_tokn **current);
bool parse_argument(t_tokn **current);
bool parse_pipeline(t_tokn **current);
bool parse_redirection(t_tokn **current);
bool parse_compound_command(t_tokn **current);
bool parse_expression(t_tokn **current);

bool	match(t_tokn **current, const char *type, const char *value)
{
    if (*current && strcmp((*current)->type, type) == 0 && 
        (!value || strcmp((*current)->value, value) == 0))
	{
        *current = (*current)->next;
        return true;
    }
    return false;
}

bool	parse_script(t_tokn **current)
{
    return (parse_command_list(current));
}

bool	parse_command_list(t_tokn **current)
{
    if (!parse_command(current))
        return false;
    while (*current && (match(current, "OPERATOR", "&&") || 
                        match(current, "OPERATOR", "||")))
       return (parse_command(current));
    return true;
}

bool	parse_command(t_tokn **current)
{
//	return (parse_simple_command(current)) || parse_pipeline(current) || parse_compound_command(current));
    if (parse_simple_command(current))
        return (true);
    if (parse_pipeline(current))
        return (true);
    if (parse_compound_command(current))
        return (true);
    return (false);
}

bool parse_simple_command(t_tokn **current)
{
    while (parse_assignment(current))
	{
	}
    if (!match(current, "WORD", NULL))
        return (false);
    while (parse_argument(current) || parse_redirection(current))
	{
	}
    return (true);
}

bool parse_assignment(t_tokn **current)
{
    t_tokn *save;
    
	save = *current;
    if (match(current, "WORD", NULL) && match(current, "OPERATOR", "="))
	{
        if (parse_expression(current))
            return true;
    }
    *current = save;
    return false;
}

bool parse_argument(t_tokn **current)
{
    return match(current, "WORD", NULL);
}

bool parse_pipeline(t_tokn **current)
{
    if (!parse_command(current))
        return false;
    while (match(current, "OPERATOR", "|"))
	{
        if (!parse_command(current))
            return false;
    }
    return true;
}

bool parse_redirection(t_tokn **current)
{
    if (match(current, "OPERATOR", ">") || match(current, "OPERATOR", ">>") ||
        match(current, "OPERATOR", "<") || match(current, "OPERATOR", "<<"))
	{
        return match(current, "WORD", NULL);
    }
    return false;
}

bool parse_compound_command(t_tokn **current)
{
    if (match(current, "OPERATOR", "(") && 
        parse_command_list(current) && 
        match(current, "OPERATOR", ")"))
	{
        return true;
    }
    return false;
}

bool parse_expression(t_tokn **current)
{
    if (match(current, "OPERATOR", "$"))
	{
        return (match(current, "WORD", NULL));
    }
    return (match(current, "WORD", NULL));
}

bool validate_syntax(t_tokn *head)
{
    t_tokn *current;
    
	current = head;
    return (parse_script(&current) && current == NULL);
}
