/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:45 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 09:55:42 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Updates the $? variable to the value of the last exit code.
void	set_error_code(t_shel **minishell, int error_code)
{
	(*minishell)->special[DCIDI] = ft_itoa(error_code);
}
