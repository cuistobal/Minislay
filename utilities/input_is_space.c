/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_is_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:03 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 10:10:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

bool	input_is_space(char *input)
{
	int	index;

	index = 0;
	while (input[index] == 32 || input[index] == 9 || input[index] == 10)
		index++;
	return (!input[index]);
}
