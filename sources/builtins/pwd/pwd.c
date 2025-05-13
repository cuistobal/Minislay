/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 08:54:47 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	pwd(char *current_dir)
{
	char	*current;
	char	temp[BUFFER_SIZE];

	current = NULL;
	memset(temp, 0, BUFFER_SIZE);
	if (getcwd(temp, BUFFER_SIZE))
	{
		current = strdup(temp);
		write(1, current, strlen(current));
		//mettre dans la struct;
	}
	write(1, current_dir, strlen(current_dir));
	//APpend error code
}
