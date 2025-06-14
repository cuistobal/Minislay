/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:48:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:15:30 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Handle logical operators: &&, ||
static char	*handle_logical_operators(const char *input, int *pos, int *type)
{
	char	*token;

	token = NULL;
	if ((input[*pos] == '&' || input[*pos] == '|') && input[*pos + 1] \
			== input[*pos] && !is_amp_pipe(input[*pos + 2]))
	{
		token = ft_strndup(input + *pos, 2);
		if (input[*pos] == '&')
			*type = LAND;
		else
			*type = LORR;
		(*pos) += 2;
	}
	return (token);
}

// Handle redirections: >>, <<, >, <
static char	*handle_redirection_tokens(const char *input, int *pos, int *type)
{
	char	*token;

	token = NULL;
	if ((input[*pos] == '>' || input[*pos] == '<') && \
			input[*pos + 1] == input[*pos])
	{
		token = ft_strndup(input + *pos, 2);
		if (input[*pos] == '>')
			*type = ARED;
		else
			*type = HDOC;
		(*pos) += 2;
	}
	else if (input[*pos] == '>' || input[*pos] == '<')
	{
		token = ft_strndup(input + *pos, 1);
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
		token = ft_strndup(input + *pos, 1);
		*type = PIPE;
		(*pos)++;
	}
	else if (input[*pos] == '(')
	{
		token = ft_strndup(input + *pos, 1);
		*type = OPAR;
		(*pos)++;
	}
	else if (input[*pos] == ')')
	{
		token = ft_strndup(input + *pos, 1);
		*type = CPAR;
		(*pos)++;
	}
	return (token);
}

//This function redirects the input towrds the right subfunction.
char	*handle_special_chars(const char *input, int *pos, int *type)
{
	char	*token;

	token = handle_logical_operators(input, pos, type);
	if (!token)
	{
		token = handle_redirection_tokens(input, pos, type);
		if (!token)
			return (handle_single_identifier(input, pos, type));
	}
	return (token);
}
