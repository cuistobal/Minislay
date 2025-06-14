/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:47:42 by chrleroy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 16:22:29 by chrleroy         ###   ########.fr       */
=======
/*   Updated: 2025/06/12 17:18:42 by ynyamets         ###   ########.fr       */
>>>>>>> feat/add_libft
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
