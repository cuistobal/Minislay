<<<<<<< HEAD
#include "minislay.h"

// Main parsing function with backtracking
bool parse_script(t_tokn *tokens) {
    t_tokn *current = tokens;
    if (tokens) 
	{
        printf("%s\t@\t%s\n", tokens->value, __func__);
	//	return parse_command_list(&current);
		parse_command_list(&current);
    }
	(current) ? printf("%s\n", current->value) : printf("NULL\n");
    return (current == NULL);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool parse_command_list(t_tokn **current) {
    t_tokn *initial_node = *current;
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if (parse_command(current)) {
            while (*current && ((*current)->type == LAND || (*current)->type == LORR)) {
                *current = (*current)->next;
                if (!parse_command(current)) {
                    return false;
                }
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexibebi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:23 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 17:17:45 by chrleroy         ###   ########.fr       */
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
    printf("%s	@	%s\n", current->value, __func__);
    if (parse_command_list(&current))
        return (true);
    current = initial_node;
    return (false);
}

// CommandList → Command ('&&' | '||') CommandList | Command
bool parse_command_list(t_tokn **current)
{
    t_tokn *initial_node;

    printf("%s	@	%s\n", (*current)->value, __func__);
    initial_node = *current;
    if (*current)
	{
		printf("%d	&&	%s\n", (*current)->type, (*current)->value);
        if (parse_command(current))
		{
			printf("%d	&&	%s\n", (*current)->type, (*current)->value);
            if ((*current)->type == LAND || (*current)->type == LORR)
			{
                *current = (*current)->next;
				return (parse_command_list(current));
            //    if (!parse_command_list(current))
			//	{
            //        *current = op_node;
            //        return (false);
            //    }
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
            }
            return true;
        }
        *current = initial_node;
    }
<<<<<<< HEAD
    return false;
=======
    return (false);
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
}

// Determine if it's a simple command, compound command, or pipeline
bool parse_command(t_tokn **current)
{
<<<<<<< HEAD
    t_tokn *initial_node;
    
	if (*current)
	{
    	printf("%s\t@\t%s\n", (*current)->value, __func__);
		initial_node = *current;
        if ((*current)->type == OPAR) {
            return parse_compound_command(current);
        } else if (parse_simple_command(current)) {
            return true;
        } else 
		{
			*current = initial_node;
            return parse_pipeline(current);
        }
    }
    return false;
}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
bool parse_simple_command(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        while ((*current)->type == WORD && (*current)->next && (*current)->next->type == EQUL) {
            if (!parse_assignment(current)) {
                return false;
            }
        }
        if ((*current)->type == WORD) {
            *current = (*current)->next;
            while (*current && ((*current)->type >= WORD && (*current)->type <= ARED)) {
                if ((*current)->type == WORD) {
                    if (!parse_argument(current)) {
                        return false;
                    }
                } else {
                    if (!parse_redirection(current)) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if (parse_command(current)) {
            while (*current && (*current)->type == PIPE) {
                *current = (*current)->next;
                if (!parse_command(current)) {
                    return false;
                }
            }
            return true;
=======
    t_tokn	*initial_node;
    bool	command_parsed;

    command_parsed = false;
    initial_node = *current;
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type == OPAR)
        command_parsed = parse_compound_command(current);
    else
        command_parsed = parse_simple_command(current);
    printf("command_parsed -> %d\n", command_parsed);
    if (command_parsed && (*current)->type == PIPE)
        return (parse_pipeline(current));
	else if ((*current)->type == LAND || (*current)->type == LORR)
		return (true);
    if (!command_parsed)
        *current = initial_node;
    return (command_parsed);
}

// SimpleCommand → Assignment* WORD (Argument | Redirection)*
bool	parse_simple_command(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type >= WORD && (*current)->type <= ARED)
	{
        parse_assignment(current);
        while ((*current)->type >= WORD && (*current)->type <= ARED)
		{
            if ((*current)->type == WORD)
			{
                parse_argument(current);
                return (parse_simple_command(current));
			}
			else
			{
				printf("redirection\n");
				parse_redirection(current);
            	return (parse_simple_command(current));
			}
        }
        return (true);
    }
    return (false);
}

// Pipeline → Command ('|' Command)*
bool parse_pipeline(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if (parse_command(current))
	{
        while ((*current)->type == PIPE)
		{
            *current = (*current)->next;
            parse_command(current);
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
        }
    }
    return false;
}

<<<<<<< HEAD
// CompoundCommand → '(' CommandList ')'
bool parse_compound_command(t_tokn **current) {
    if (*current && (*current)->type == OPAR) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
=======
bool parse_compound_command(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type == OPAR)
	{
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
        *current = (*current)->next;
        if (parse_command_list(current)) {
            if ((*current)->type == CPAR) {
                *current = (*current)->next;
                return true;
            }
        }
    }
    return false;
}

// Assignment → WORD '=' Expression
<<<<<<< HEAD
bool parse_assignment(t_tokn **current) {
    if (*current && (*current)->next) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if ((*current)->type == WORD && (*current)->next->type == EQUL) {
=======
bool parse_assignment(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if (*current && (*current)->next)
	{
        if ((*current)->type == WORD && (*current)->next->type == EQUL)
		{
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
            *current = (*current)->next->next;
            return parse_expression(current);
        }
    }
    return false;
}

// Argument → WORD
<<<<<<< HEAD
bool parse_argument(t_tokn **current) {
    if (*current && (*current)->type == WORD) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
=======
bool	parse_argument(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type == WORD)
	{
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
        *current = (*current)->next;
        return true;
    }
    return false;
}

// Redirection → ('>' | '>>' | '<' | '<<') WORD
<<<<<<< HEAD
bool parse_redirection(t_tokn **current) {
    if (*current && ((*current)->type >= IRED && (*current)->type <= ARED)) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
=======
bool	parse_redirection(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type >= IRED && (*current)->type <= ARED)
	{
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
        *current = (*current)->next;
        if ((*current)->type == WORD) {
            *current = (*current)->next;
            return true;
        }
    }
    return false;
}

// Expression → '$' WORD | WORD
<<<<<<< HEAD
bool parse_expression(t_tokn **current) {
    if (*current) {
        printf("%s\t@\t%s\n", (*current)->value, __func__);
        if ((*current)->type == DOLL) {
            *current = (*current)->next;
        }
        return parse_argument(current);
=======
bool	parse_expression(t_tokn **current)
{
    printf("%s	@	%s\n", (*current)->value, __func__);
    if ((*current)->type == DOLL)
	{
        *current = (*current)->next;
        return (parse_argument(current));
>>>>>>> parent of db66c36 (Ca marche dans 1 cas xd)
    }
    return false;
}
