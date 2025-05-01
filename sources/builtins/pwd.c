/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/25 11:38:41 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	pwd(char *current_dir)
{
	char	*current;
	char	temp[BSIZE];

	current = NULL;
	memset(temp, 0, BSIZE);
	if (getcwd(temp, BSIZE))
	{
		current = strdup(temp);
		write(1, current, strlen(current));
		//mettre dans la struct;
	}
	write(1, current_dir, strlen(current_dir));
	//APpend error code
}
