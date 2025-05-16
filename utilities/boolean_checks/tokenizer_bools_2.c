/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:57:33 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/04 13:59:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Checking if we have an opening or closing parenthesis
bool	is_paren(char c)
{
	return (c == '(' || c == ')');
}

//Checking if we have a single quote
bool	is_squotes(char c)
{
	return (c == '\'');
}

//Checking if we have a double quote
bool	is_dquotes(char c)
{
	return (c == '"');
}

//Checking if we have a input redirection
bool	is_iredir(char c)
{
	return (c == '<');
}

//Checking if we have an outpute redirection
bool	is_oredir(char c)
{
	return (c == '>');
}
