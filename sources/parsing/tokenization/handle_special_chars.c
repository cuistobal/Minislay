/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:48:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/17 11:01:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Handle logical operators: &&, ||
static char	*handle_logical_operators(const char *input, int *pos, int *type)
{
	char	*token;

	token = NULL;
    if ((input[*pos] == '&' || input[*pos] == '|') && input[*pos + 1] == input[*pos])
	{
        token = strndup(input + *pos, 2);
        if (input[*pos] == '&')
            *type = LAND;
        else
            *type = LORR;
        (*pos) += 2;
    }
    return (token);
}

// Handle redirections: >>, <<, >, <
static char	*handle_redirections(const char *input, int *pos, int *type)
{
	char	*token;

	token = NULL;
    if ((input[*pos] == '>' || input[*pos] == '<') && input[*pos + 1] == input[*pos])
	{
		token = strndup(input + *pos, 2);
        if (input[*pos] == '>')
            *type = ARED;
        else
            *type = HDOC;
        (*pos) += 2;
    }
	else if (input[*pos] == '>' || input[*pos] == '<')
	{
        token = strndup(input + *pos, 1);
        if (input[*pos] == '>')
            *type = ORED;
        else
            *type = IRED;
        (*pos)++;
    }
    return (token);
}

// Handle single characters: | -> returns NULL if we send a single &
// EDGE case here
static char	*handle_single_identifier(const char *input, int *pos, int *type)
{
	char	*token;

	token = NULL;
    if (input[*pos] == '|')
	{
        token = strndup(input + *pos, 1);
        *type = PIPE;
        (*pos)++;
    }
    else if (input[*pos] == '(')
    {        
        token = strndup(input + *pos, 1);
        *type = OPAR;
        (*pos)++;
    }
    else if (input[*pos] == ')')
    {
        token = strndup(input + *pos, 1);
        *type = CPAR;
        (*pos)++;
    }
    return (token);
}

char	*handle_special_chars(const char *input, int *pos, int *type)
{
    char    *token;

    token = handle_logical_operators(input, pos, type);
    if (token != NULL)
		return (token);
    token = handle_redirections(input, pos, type);
    if (token != NULL)
		return (token);
	return (handle_single_identifier(input, pos, type));
}
