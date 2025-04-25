/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:47:42 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/25 09:49:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	error_message(char *message)
{
	return (write(2, message, strlen(message)), false);
}
