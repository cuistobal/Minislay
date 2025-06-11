/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:26:27 by ynyamets          #+#    #+#             */
/*   Updated: 2025/06/11 17:30:27 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	free_array(char **array, int count)
{
	int	index;

	index = 0;
	if (!*array)
		return ;
	if (count > 0)
	{
		while (count--)
		{
			free(array[count]);
			array[count] = NULL;
		}
	}
	else
	{
		while (array[index])
		{
			free(array[index]);
			array[index] = NULL;
			index++;
		}
	}
	free(array);
	array = NULL;
}
