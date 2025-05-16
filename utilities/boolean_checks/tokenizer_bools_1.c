/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:55:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/25 14:41:58 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minislay.h>

//Checking if we have a pipe or amp token
bool	is_amp_pipe(char c)
{
	return (c == '&' || c == '|');
}

//Checking if we have a whitespace token
bool	is_whitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ');
}

//Checking if we have a expansion token
bool	is_var_wild(char c)
{
	return (c == '$' || c == '*' || c == '=');
}

//Checking if we have a redirection token
bool	is_redir(char c)
{
	return (is_iredir(c) || is_oredir(c));
}

//Checking if we have either a single or a double quote
bool	is_quote(char c)
{
	return (is_squotes(c) || is_dquotes(c));
}
