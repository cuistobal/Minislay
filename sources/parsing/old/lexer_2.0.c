/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:10:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/09 11:47:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token structure
typedef struct tokens 
{
    char *type;   // Token type (e.g., WORD, OPERATOR, etc.)
    char *value;  // Token value (actual text)
    struct tokens *next;
} t_tokn;

// Function prototypes
int parse_script(t_tokn **current);
int parse_command_list(t_tokn **current);
int parse_command(t_tokn **current);
int parse_simple_command(t_tokn **current);
int parse_assignment(t_tokn **current);
int parse_argument(t_tokn **current);
int parse_pipeline(t_tokn **current);
int parse_redirection(t_tokn **current);
int parse_compound_command(t_tokn **current);
int parse_expression(t_tokn **current);

// Utility function to match token and advance
int match(t_tokn **current, const char *type, const char *value)
{
    if (*current && strcmp((*current)->type, type) == 0 && (!value || strcmp((*current)->value, value) == 0))
	{
        *current = (*current)->next;
        return 1;
    }
    return 0;
}

// Recursive Descent Parsing Functions

int parse_script(t_tokn **current)
{
    return parse_command_list(current);
}

int parse_command_list(t_tokn **current)
{
    if (!parse_command(current))
		return 0;
    while (*current && (match(current, "OPERATOR", "&&") || match(current, "OPERATOR", "||")))
	{
        if (!parse_command(current))
			return 0;
    }
    return 1;
}

int parse_command(t_tokn **current)
{
    return parse_simple_command(current) || parse_pipeline(current) || parse_compound_command(current);
}

int parse_simple_command(t_tokn **current)
{
    while (parse_assignment(current));  // Zero or more assignments
    	if (!match(current, "WORD", NULL))
			return 0;  // Command name
    while (parse_argument(current) || parse_redirection(current));  // Arguments or Redirections
    	return 1;
}

int parse_assignment(t_tokn **current)
{
    t_tokn *save = *current;
    if (match(current, "WORD", NULL) && match(current, "OPERATOR", "="))
	{
        if (parse_expression(current))
			return 1;
    }
    *current = save;
    return 0;
}

int parse_argument(t_tokn **current)
{
    return match(current, "WORD", NULL);
}

int parse_pipeline(t_tokn **current)
{
    if (!parse_command(current))
		return 0;
    while (match(current, "OPERATOR", "|"))
	{
        if (!parse_command(current))
			return 0;
    }
    return 1;
}

int parse_redirection(t_tokn **current)
{
    if (match(current, "OPERATOR", ">") || match(current, "OPERATOR", ">>") ||
        match(current, "OPERATOR", "<") || match(current, "OPERATOR", "<<"))
	{
        return match(current, "WORD", NULL);
    }
    return 0;
}

int parse_compound_command(t_tokn **current)
{
    if (match(current, "OPERATOR", "(") && parse_command_list(current) && match(current, "OPERATOR", ")"))
	{
        return 1;
    }
    return 0;
}

int parse_expression(t_tokn **current)
{
    return (match(current, "OPERATOR", "$") && match(current, "WORD", NULL)) || match(current, "WORD", NULL);
}

// Entry point to validate the linked list
int validate_syntax(t_tokn *head)
{
    t_tokn *current = head;
    return parse_script(&current) && current == NULL;  // Ensure all tokens are consumed
}
