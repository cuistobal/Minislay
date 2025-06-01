/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:38:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 09:47:56 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	*resize_array(void *array, int array_type, int *size)
{
	int		len;
	void	*new;

	len = *size;
	if (!array)
	{	
		new = realloc(array, array_type * *size);
		if (!new)
			return (NULL);
		memset(new, 0, array_type * len);
	}
	else
	{
		*size = *size << 1;
		new = realloc(array, array_type * *size);
		if (!new)
			return (NULL);
		memset(new + (array_type * len), 0, (array_type * len));
	}
	return (new);
}

//
void	reset_array(char **array, int start, int end)
{
	int	reset;

	reset = 0;
	if (!array)
		return ;
	while (reset < end - start)
		array[start + reset++] = NULL;
}
