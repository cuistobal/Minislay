/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:38:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 21:26:31 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	*resize_array(void *array, int elem_size, int *size)
{
	void	*new;
	int		old_size;
	int		new_size;

	old_size = *size;
	if (!array)
	{
		new = malloc(elem_size * old_size);
		if (!new)
			return (NULL);
		ft_memset(new, 0, elem_size * old_size);
		return (new);
	}
	*size = old_size << 1;
	new_size = *size;
	new = malloc(elem_size * new_size);
	if (!new)
		return (NULL);
	ft_memcpy(new, array, elem_size * old_size);
	ft_memset((char *)new + (elem_size * old_size), 0, elem_size * old_size);
	free(array);
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
