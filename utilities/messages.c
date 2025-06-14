/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:47:42 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 18:53:41 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	error_message(char *message)
{
	return (write(2, message, ft_strlen(message)), false);
}

bool	parsing_error(char *token)
{
	error_message(BASH);
	error_message(SYNTAX);
	error_message(UNEXPECTED);
	error_message(token);
	return (error_message("\n"));
}

bool	parenthesis_error(void)
{
	error_message(BASH);
	error_message(SYNTAX);
	return (error_message(UNMATCHED_PAR));
}
